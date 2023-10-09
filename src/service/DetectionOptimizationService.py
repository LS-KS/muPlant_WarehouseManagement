"""
Genetic algorithm to calculate optimal detection parameters for aruco marker detection.
Problem was, that default settings did not detect all aruco markers reliably.
The parameters consists of 32 attributes and minor changes in just one attribute may lead to
complete failure in detection.
Idea developed from just a for-loop to test all possible combinations of parameters.
Problem was that documentation of opencv.aruco doesnot provide any information about the
limits of the parameters. So it was not possible to iterate over all possible combinations.
Therefore a genetic algorithm was implemented to find the best parameters by exploring the
parameter space randomly.

Some parameters are boolean, some are integers and some are floats.
The ga is not binary coded. float parameters are mutated by a normal distributed random number
while boolean parameters are just flipped be either be choosed randomly (initialization) or flipped (mutation).
Integer parameters are calculated by the same way but just rounded.

The random multiplier in mutation is a normal distributed random number with mean 1 and a deviation of 1.
This number is multiplied by the mutation rate to get more diversity.

"""


import cv2
import numpy as np
from matplotlib import pyplot as plt
import random
from yaml import dump
from tqdm import tqdm
from time import time
from src.constants.Constants import Constants

class Individual:
    """
    class to keep individual and fitness property together.
    """
    def __init__(self):
        self.parameters = None
        self.fitness = None

class DetectionOptimizationService:
    """
    Service to optimize detection parameters for aruco markers.
    """
    # List of attributes to be considered for recombination
    attribute_names = [
        "adaptiveThreshWinSizeMin",
        "adaptiveThreshWinSizeMax",
        "adaptiveThreshWinSizeStep",
        "adaptiveThreshConstant",
        "minMarkerPerimeterRate",
        "maxMarkerPerimeterRate",
        "polygonalApproxAccuracyRate",
        "minCornerDistanceRate",
        "minDistanceToBorder",
        "minMarkerDistanceRate",
        "cornerRefinementMethod",
        "cornerRefinementWinSize",
        "cornerRefinementMaxIterations",
        "cornerRefinementMinAccuracy",
        "markerBorderBits",
        "perspectiveRemovePixelPerCell",
        "perspectiveRemoveIgnoredMarginPerCell",
        "maxErroneousBitsInBorderRate",
        "minOtsuStdDev",
        "errorCorrectionRate",
        "aprilTagQuadDecimate",
        "aprilTagQuadSigma",
        "aprilTagMinClusterPixels",
        "aprilTagMaxNmaxima",
        "aprilTagCriticalRad",
        "aprilTagMaxLineFitMse",
        "aprilTagMinWhiteBlackDiff",
        "aprilTagDeglitch",
        "detectInvertedMarker",
        "useAruco3Detection",
        "minSideLengthCanonicalImg",
        "minMarkerLengthRatioOriginalImg",
    ]
    def __init__(self):
        self.errors: int = 0
        self.errors_generation = []
        self.pop_size = 1000
        self.mut_prob = 0.01
        self.mut_rate = 0.1
        self.max_iter = 10
        self.tournament_size = 2
        self.tournament_winner_count = 20
        self.constants = Constants()
        self.cups = []
        self.cup_id = self.constants.CUP_ARUCO
        self.pallets = []
        self.pallet_id = self.constants.PALLET_ARUCO
        self.cell = []
        self.cell_id = self.constants.SHELF_ARUCO
        self.arucodict = cv2.aruco.getPredefinedDictionary(cv2.aruco.DICT_6X6_250)
        self.UPPER_LEFT = (0, 1, 2, 6, 7, 8)
        self.UPPER_RIGHT = (3, 4, 5, 9, 10, 11)
        self.LOWER_RIGHT = (9, 10, 11, 15, 16, 17)
        self.LOWER_LEFT = (6, 7, 8, 12, 13, 14)
        self.load_images()
        self.results = None
    def optimize_cups(self):
        """
        This function will optimize the detection parameters for cup markers.
        """
        self.run_ga('cup')
        self.plot_results('cup')
        fittest_generation = sorted(self.results, key=lambda x: x[3], reverse=True)[0]
        fittest_individual = fittest_generation[4]
        self.dump_parameters(fittest_individual.parameters, '../data/Cups.yaml')
    def optimize_pallets(self):
        """
        This function will optimize the detection parameters for pallet markers.
        """
        self.run_ga('pallet')
        self.plot_results('pallets')
        fittest_generation = sorted(self.results, key=lambda x: x[3], reverse=True)[0]
        fittest_individual = fittest_generation[4]
        self.dump_parameters(fittest_individual.parameters, '../data/Pallets.yaml')
    def optimize_shelves(self):
        """
        This function will optimize the detection parameters for shelf markers.
        """
        self.run_ga('cell')
        self.plot_results('cell')
        fittest_generation = sorted(self.results, key=lambda x: x[3], reverse=True)[0]
        fittest_individual = fittest_generation[4]
        self.dump_parameters(fittest_individual.parameters, '../data/Cell.yaml')
    def load_images(self):
        """
        This function will load the images for the optimization from src/service directory.
        """
        self.cell = automatic_brightness_and_contrast(cv2.imread("processed_before_detection.png"), 1)
        for i in range(18):
            self.cups.append(cv2.imread('cup' + str(i + 1) + '.png'))
            self.pallets.append(cv2.imread('pallet_' + str(i + 1) + '.png'))
    def evaluate_fitness(self,parameters: cv2.aruco.DetectorParameters, t: str)  -> int:
        """
        Calculates fittness of an Individual object's parameters attribute by detecting selected marker types.
        fitness is increased by 1 for each correctly detected marker.
        fitness is decreased by 1 if an error occurs.
        :param parameters: parameters attribute of Individual object
        :type parameters: cv2.aruco.DetectorParameters
        :param t: type of marker to be detected could be either 'cups', 'pallets' or 'cell'
        :type t: str
        :returns points: fitness value
        :rtype: int
        """
        start = time()
        points = 0
        if t == 'cup':
            images = self.cups
        elif t == 'pallet':
            images = self.pallets
        elif t == 'cell':
            images = [self.cell]
        for i, img in enumerate(images):
            try:
                corners, ids, rejected = cv2.aruco.detectMarkers(img, self.arucodict, parameters=parameters)
                if ids is not None:
                    for j, id in enumerate(ids):
                        target = getattr(self, f"{t}_id")
                        got = id[0]
                        if type(target) == int:
                            if got == target:
                                points += 2
                        elif got in target:
                            points += 2
            except Exception as e:
                points -= 1
                self.errors += 1
                #print(f"Error occured, fitness reduced. total errors in {type}: {self.errors}\n{e}")
        end = time()
        points += int(end - start)
        return points
    def create_population(self) -> list[Individual]:
        """
        This function creates a list with random initialized Individual objects.
        The kind of random initialization depends on attribute datatype.
        Knowledge from opencv.aruco documentation was used to determine the range of values for each attribute.
        https://docs.opencv.org/4.x/d5/dae/tutorial_aruco_detection.html
        :return population:
        :rtype: list[Individual]
        """
        start = time()
        population = []
        for i in range(self.pop_size):
            parameters = cv2.aruco.DetectorParameters()
            # Parameter for thresholding
            #ThreshWinSizeMin / ThreshWinSizeMax represent the interval in pixels where the thresholding sizes are selected for the adaptive thresholding
            parameters.adaptiveThreshWinSizeMin = int(random.randrange(3, 50, 1))
            # WinSizeMax must be greater than WinSizeMin
            while  parameters.adaptiveThreshWinSizeMax <= parameters.adaptiveThreshWinSizeMin + 3:
                parameters.adaptiveThreshWinSizeMax = int(random.randrange(3, 100, 1))
            # Since WinSizeStep is the iteration step size it must fit at least once into the difference between WinSizeMin and WinSizeMax
            while parameters.adaptiveThreshWinSizeMax - parameters.adaptiveThreshWinSizeMin <= parameters.adaptiveThreshWinSizeStep:
                parameters.adaptiveThreshWinSizeStep = int(random.randrange(3, 100, 1))
            # ThreshConstant isis used in threshold() function. Default is 7 and recommended. So creation will vary around default value.
            parameters.adaptiveThreshConstant *= np.random.rand() + 0.5

            # Parameter for contour recognition
            # minMarkerPerimeterRate / maxMarkerPerimeterRate determine the minimum and maximum size
            # of a marker in relation to the image size (not actual pixel size)
            # hence there are boundaries for the values.
            while parameters.minMarkerPerimeterRate>= parameters.maxMarkerPerimeterRate:
                parameters.minMarkerPerimeterRate = np.random.rand()
                parameters.maxMarkerPerimeterRate = np.random.rand()
            # polygonalApproxAccuracyRate determines the maximum allowed error for the polygonal approximation to the marker contour.
            # the more distorted the image is, the higher this rate should be and vice versa
            parameters.polygonalApproxAccuracyRate = np.random.rand()

            # determinse the minimum distance between two corners in a marker. value is relative to marker size.
            parameters.minCornerDistanceRate = np.random.rand()

            # minMerkerDistanceRate determines the minimum distance between two corners of different markers in the image.
            # value is relative to min marker perimeter value.
            parameters.minMarkerDistanceRate = np.random.rand()
            # minimum distance from image border to marker in pixels
            parameters.minDistanceToBorder = int(random.randrange(0, 1000, 1))

            # Bits extraction parameters
            # markerBorderBits determines the marker borderwidth it is relative to the size of each bit.
            # Since markers are created in a way where the border has the same size as the bits,
            # this value should be only allowed to vary around 1 in a small interval.
            # since required datatype is int, the value shouldnt be varied in any way ?!?
            parameters.markerBorderBits = 1
            parameters.minOtsuStdDev = np.random.rand()


            parameters.perspectiveRemovePixelPerCell = random.randrange(4, 1000, 1)
            parameters.perspectiveRemoveIgnoredMarginPerCell = np.random.rand()

            # Marker identification parameters
            parameters.maxErroneousBitsInBorderRate = np.random.rand()
            # too high rate can lead to false positive pixels.
            parameters.errorCorrectionRate = np.random.rand() + 0.35

            # Corner Refinement Parameters are not used in this usecase this position of the markers is not that important
            # parameters.cornerRefinementMethod *= int(np.ceil((np.random.normal(0, 1) + 1)))
            # parameters.cornerRefinementWinSize *= int(np.ceil((np.random.normal(0, 1) + 1)))
            # parameters.cornerRefinementMaxIterations *= int(np.ceil((np.random.normal(0, 1) + 1)))
            # parameters.cornerRefinementMinAccuracy *= (np.random.normal(0, 1) + 1)
            # parameters.aprilTagQuadDecimate *= (np.random.normal(0, 1) + 1)
            # parameters.aprilTagQuadSigma *= (np.random.normal(0, 1) + 1)
            # parameters.aprilTagMinClusterPixels *= int(np.ceil((np.random.normal(0, 1) + 1)))
            # parameters.aprilTagMaxNmaxima *= int(np.ceil((np.random.normal(0, 1) + 1)))
            # parameters.aprilTagCriticalRad *= (np.random.normal(0, 1) + 1)
            # parameters.aprilTagMaxLineFitMse *= (np.random.normal(0, 1) + 1)
            # parameters.aprilTagMinWhiteBlackDiff *= int(np.ceil((np.random.normal(0, 1) + 1)))
            # parameters.aprilTagDeglitch *= int(np.ceil((np.random.normal(0, 1) + 1)))
            # parameters.detectInvertedMarker = random.choice([True, False])
            # parameters.useAruco3Detection = random.choice([True, False])
            # parameters.minSideLengthCanonicalImg *= int(np.ceil((np.random.normal(0, 1) + 1)))
            # parameters.minMarkerLengthRatioOriginalImg *= (np.random.normal(0, 1) + 1)
            
            # create Indivisual instance with parameters and append to population
            individual = Individual()
            individual.parameters = parameters
            population.append(individual)
        end = time()
        print(f'Population of {str(len(population))} created in {end - start} seconds')
        return population
    def mutate_parameter(self, individual: Individual) -> Individual:
        """
        Function to mutate attributes of one Individual object.
        :param individual: Individual object
        :type individual: Individual
        :returns individual: mutated Individual object
        :rtype: Individual
        """
        for field in self.attribute_names:
            value = getattr(individual.parameters, field)
            if np.random.rand() < self.mut_prob:
                if type(value) == int:
                    value = int(value * (1 + random.randrange(-1,1)* self.mut_rate))
                elif type(value) == float:
                    value *= (1 + random.randrange(-1,1)* self.mut_rate)
                elif type(value) == bool:
                    value = random.choice([True, False])
                setattr(individual.parameters, field, value)
        return individual
    def recombine_parameters(self, parent1: Individual, parent2: Individual) -> Individual:
        """
        Takes two Individual objects as parents and randomly recombines attribute values into a child object.
        :param parent1: Individual object as parent
        :type parent1: Individual
        :param parent2: another Individual object as parent
        :type parent2: Individual
        :returns child: child object with attribute values randomly selected from parents
        :rtype: Individual
        """
        child = Individual()
        child.parameters = cv2.aruco.DetectorParameters()
        for field in self.attribute_names:
            value1 = getattr(parent1.parameters, field)
            value2 = getattr(parent2.parameters, field)
            if np.random.rand() < 0.5:
                setattr(child.parameters, field, value1)
            else:
                setattr(child.parameters, field, value2)
        return child
    def tournament_selection(self, population: list[Individual], tournament_size: int) -> Individual:
        """
        function to select fittest individual from tournament in population.
        tournament_size individuals are selected and the fittest individual is returned.

        :param population: population
        :type population: list[Individual]
        :param tournament_size: determines the group size out of which the fittest indivisual is selected
        :type tournament_size: int
        :returns: instance of Individual (fittest in tournament)
        """
        competitors = [x for x in population if x.fitness > 0]
        if len(competitors) < tournament_size:
            competitors = random.sample(population, k=tournament_size)
        else:
            competitors = random.sample(competitors, k=tournament_size)
        fittest = sorted(competitors, key=lambda x: x.fitness, reverse=True)[0]
        return fittest
    def dump_parameters(self, parameters: cv2.aruco.DetectorParameters, filename: str):
        data = {}
        for field in self.attribute_names:
            data[field] = getattr(parameters, field)
        with open(filename, 'w') as file:
            dump(data, file)
    def plot_results(self, type:str):
        """
        creates a simple plot to plot results of genetic algorithm against together with parameters.
        :param type: for text generation: 'cup', 'pallet' or 'shelf'
        :type type: str
        """
        # plot results
        runs = [result[0] for result in self.results]
        max_fitness = [result[3] for result in self.results]
        mean_fitness = [result[2] for result in self.results]
        plt.plot(runs, max_fitness, label='max')
        plt.plot(runs, mean_fitness, label='mean')
        plt.title(f'Fitness over generations for {type} markers')
        plt.xlabel('Generation')
        plt.ylabel(f'Fitness (number of detected {type} markers)')
        plt.legend()
        plt.text(0.5, 0.5,
                 f'population size: {self.pop_size}\nmutation probability: {self.mut_prob}\nmutation rate: {self.mut_rate}\nmax gen: {self.max_iter}\ntournament size: {self.tournament_size}\ntournament winner: {self.tournament_winner_count}')
        plt.savefig(fname=f'ga_{type}_result.png')
        plt.show()
    def run_ga(self, type:str):
        self.results = []
        self.errors_generation = []
        # create initial population and evaluate fitness
        pop = self.create_population()
        self.errors = 0
        for i in tqdm(range(self.max_iter), desc=f'Running GA ({type})', leave=False):
            # evaluate fitness
            self.errors_generation.append([i, []])
            for j in tqdm(range(len(pop)), desc = f'Generation {i} ({type})', leave=False):
                individual = pop[j]
                individual.fitness = self.evaluate_fitness(individual.parameters, type)
            # save results
            self.results.append([i, pop, np.mean([individual.fitness for individual in pop]),
                            np.max([individual.fitness for individual in pop]),
                            sorted(pop, key=lambda x: x.fitness, reverse=True)[0]])
            self.errors_generation.append([i, self.errors])
            self.errors = 0
            print(f'Generation {i} ({type})\nFitness evaluation:\nMean: {self.results[i][2]}\nMax: {self.results[i][3]}')
            print(f'Erroring individuals: {self.errors_generation[i][1]}')
            # select fittest for recombination
            new_pop = []
            for j in range(self.tournament_winner_count):
                new_pop.append(self.tournament_selection(pop, self.tournament_size))
            # recombine missing individuals
            for k in range(self.pop_size - self.tournament_winner_count):
                parent1 = random.choice(new_pop[0: self.tournament_winner_count])
                parent2 = random.choice(new_pop[0: self.tournament_winner_count])
                new_pop.append(self.recombine_parameters(parent1, parent2))
            # mutate population bad elites from previous generation and recombined individuals
            for l in range(self.pop_size):
                if l < self.tournament_winner_count:
                    if new_pop[l].fitness < 1:
                        new_pop[l] = self.mutate_parameter(new_pop[l])
                else:
                    new_pop[l] = self.mutate_parameter(new_pop[l])
            pop = new_pop
            self.dump_parameters(self.results[i][4].parameters, f'ga_{type}_resultGen{i+1}.yaml')
def automatic_brightness_and_contrast(image,  clip_hist_percent):
   """
   Autoadjusting color and brightness for better marker detection.
   Source: Stackoverflow
   https://stackoverflow.com/questions/56905592/automatic-contrast-and-brightness-adjustment-of-a-color-photo-of-a-sheet-of-pape
   """
   gray = image
   # Calculate grayscale histogram
   hist = cv2.calcHist(gray, [0], None, [256], [0,256])
   hist_size = len(hist)
   # Calculate cumulativ distribution from the histogram
   accumulator = []
   accumulator.append(float(hist[0]))
   for index in range(1, hist_size):
       accumulator.append(accumulator[index-1]+float(hist[index]))
   # Locate points to clip
   maximum = accumulator[-1]
   clip_hist_percent *= (maximum/100)
   clip_hist_percent /=2
   # Locate left cut
   minimum_gray = 0
   while accumulator[minimum_gray] < clip_hist_percent:
       minimum_gray +=1
   # Locate right cut
   maximum_gray = hist_size-1
   while accumulator[maximum_gray] >= (maximum - clip_hist_percent):
       maximum_gray -= 1
   # Calculate alpha and beta values
   if maximum_gray -minimum_gray !=0:
       alpha = 255/(maximum_gray - minimum_gray)
       beta = -minimum_gray * alpha
       # Calculate new histogram with desired range and show histogram
       # new_hist = cv2.calcHist([gray], [0], None, [256], [minimum_gray, maximum_gray])
       # plt.plot(hist)
       # plt.plot(new_hist)
       # plt.xlim([0, 256])
       # plt.show()
       # print(alpha, beta)
       img = cv2.convertScaleAbs(gray, alpha= alpha, beta=beta)
       cv2.imwrite("processed_before_detection.png", img)
       #plt.imshow(img, cmap= 'gray')
       #plt.show()
       return img
   else:
       return gray


if __name__ == '__main__':
    do = DetectionOptimizationService()
    do.optimize_shelves()
    # do.optimize_cups()
    # do.optimize_pallets()


