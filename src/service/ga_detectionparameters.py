import cv2
import numpy as np
from matplotlib import pyplot as plt
import random
from yaml import dump
from tqdm import tqdm

class Individual:
    """
    class to keep individual and fitness property together.
    """
    def __init__(self):
        self.parameters = None
        self.fitness = None


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
    "minMarkerLengthRatioOriginalImg"
]


def evaluate_fitness_cups(parameters: cv2.aruco.DetectorParameters) -> int:
    """
    Calculates fittness of an Individual object's parameters attribute by detecting markers of an imageset of cup markers.
    If a marker is detected (detected a valid marker ID) fitness is increased by 1.
    If an error occurs while detecting, fitness is decreased by 1.
    :param parameters: parameters attribute of Individual object
    :type parameters: cv2.aruco.DetectorParameters
    :returns points: fitness value
    :rtype: int
    """
    arucodict = cv2.aruco.getPredefinedDictionary(cv2.aruco.DICT_6X6_250)
    points = 0
    for i, cup in enumerate(cups):
        try:
            corners, ids, rejected = cv2.aruco.detectMarkers(cup, arucodict, parameters=parameters)
            if ids is not None:
                points += 1
        except Exception as e:
            points -= 1
    return points
def evaluate_fitness_pallet(parameters: cv2.aruco.DetectorParameters) -> int:
    """
    Calculates fittness of an Individual object's parameters attribute by detecting markers of an imageset of pallet markers.
    If a marker is detected (detected a valid marker ID) fitness is increased by 1.
    If an error occurs while detecting, fitness is decreased by 1.
    :param parameters: parameters attribute of Individual object
    :type parameters: cv2.aruco.DetectorParameters
    :returns points: fitness value
    :rtype: int
    """
    arucodict = cv2.aruco.getPredefinedDictionary(cv2.aruco.DICT_6X6_250)
    points = 0
    for i, pallet in enumerate(pallets):
        try:
            corners, ids, rejected = cv2.aruco.detectMarkers(pallet, arucodict, parameters=parameters)
            if ids is not None:
                points += 1
        except Exception as e:
            points -= 1
    return points
def mutate_parameter(individual: Individual, mut_prob: float, mut_rate: float) -> Individual:
    """
    Function to mutate attributes of one Individual object.
    :param individual: Individual object
    :type individual: Individual
    :param mut_prob: probability which determines if an attribute is mutated or not.
    :type mut_prob: float
    :param mut_rate: Amount of mutation applied if mutation occurs. For more diversification it is multiplied by a normal distributed random number between 0 and 1
    :type mut_rate: float
    :returns individual: mutated Individual object
    :rtype: Individual
    """
    for field in attribute_names:
        value = getattr(individual.parameters, field)
        if np.random.rand() < mut_prob:
            if type(value) == int:
                value = int(value + np.random.normal(0,1) * mut_rate)
            elif type(value) == float:
                value = value + np.random.normal(0,1) * mut_rate
            elif type(value) == bool:
                value = not value
            setattr(individual.parameters, field, value)
    return individual
def recombine_parameters(parent1: Individual, parent2: Individual) -> Individual:
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
    for field in attribute_names:
        value1 = getattr(parent1.parameters, field)
        value2 = getattr(parent2.parameters, field)
        if np.random.rand() < 0.5:
            setattr(child.parameters, field, value1)
        else:
            setattr(child.parameters, field, value2)
    return child
def create_population(pop_size: int) -> list[Individual]:
    """
    This function creates a list with random initialized Individual objects.
    The kind of random initialization depends on attribute datatype. Could be more automated

    :param pop_size: List size
    :type pop_size: int
    :return population:
    :rtype: list[Individual]
    """
    population = []
    for i in range(pop_size):
        parameters = cv2.aruco.DetectorParameters()
        parameters.adaptiveThreshWinSizeMin *= int(np.ceil((np.random.normal(0,1)+1)))
        parameters.adaptiveThreshWinSizeMax *= int(np.ceil((np.random.normal(0,1)+1)))
        parameters.adaptiveThreshWinSizeStep *= int(np.ceil((np.random.normal(0,1)+1)))
        parameters.adaptiveThreshConstant *= (np.random.normal(0,1)+1)
        parameters.minMarkerPerimeterRate *= (np.random.normal(0,1)+1)
        parameters.maxMarkerPerimeterRate *= (np.random.normal(0,1)+1)
        parameters.polygonalApproxAccuracyRate *= (np.random.normal(0,1)+1)
        parameters.minCornerDistanceRate *= (np.random.normal(0,1)+1)
        parameters.minDistanceToBorder *= int(np.ceil((np.random.normal(0,1)+1)))
        parameters.minMarkerDistanceRate *= (np.random.normal(0,1)+1)
        parameters.cornerRefinementMethod *= int(np.ceil((np.random.normal(0,1)+1)))
        parameters.cornerRefinementWinSize *= int(np.ceil((np.random.normal(0,1)+1)))
        parameters.cornerRefinementMaxIterations *= int(np.ceil((np.random.normal(0,1)+1)))
        parameters.cornerRefinementMinAccuracy *= (np.random.normal(0,1)+1)
        parameters.markerBorderBits *= int(np.ceil((np.random.normal(0,1)+1)))
        parameters.perspectiveRemovePixelPerCell *= int(np.ceil((np.random.normal(0,1)+1)))
        parameters.perspectiveRemoveIgnoredMarginPerCell *= (np.random.normal(0,1)+1)
        parameters.maxErroneousBitsInBorderRate *= (np.random.normal(0,1)+1)
        parameters.minOtsuStdDev *= (np.random.normal(0,1)+1)
        parameters.errorCorrectionRate *= (np.random.normal(0,1)+1)
        parameters.aprilTagQuadDecimate *= (np.random.normal(0,1)+1)
        parameters.aprilTagQuadSigma *= (np.random.normal(0,1)+1)
        parameters.aprilTagMinClusterPixels *= int(np.ceil((np.random.normal(0,1)+1)))
        parameters.aprilTagMaxNmaxima *= int(np.ceil((np.random.normal(0,1)+1)))
        parameters.aprilTagCriticalRad *= (np.random.normal(0,1)+1)
        parameters.aprilTagMaxLineFitMse *= (np.random.normal(0,1)+1)
        parameters.aprilTagMinWhiteBlackDiff *= int(np.ceil((np.random.normal(0,1)+1)))
        parameters.aprilTagDeglitch *= int(np.ceil((np.random.normal(0,1)+1)))
        parameters.detectInvertedMarker = random.choice([True, False])
        parameters.useAruco3Detection = random.choice([True, False])
        parameters.minSideLengthCanonicalImg *= int(np.ceil((np.random.normal(0,1)+1)))
        parameters.minMarkerLengthRatioOriginalImg *= (np.random.normal(0,1)+1)
        individual = Individual()
        individual.parameters = parameters
        population.append(individual)
    return population
def dump_parameters(parameters: cv2.aruco.DetectorParameters, filename: str):
    data = {}
    for field in attribute_names:
        data[field] = getattr(parameters, field)
    with open(filename, 'w') as file:
        dump(data, file)
def plot_results_cups(results: list, pop_size: int, mut_prob: float, mut_rate: float, max_iter: int, tournament_size: int, tournament_winner_count: int):
    """
    creates a simple plot to plot results of genetic algorithm against cup markers together with parameters.

    :param results: list of results
    :type results: list
    :param pop_size: population size
    :type pop_size: int
    :param mut_prob: mutation probability
    :type mut_prop: float
    :param mut_rate: mutation rate
    :type mut_prob: float
    :param max_iter: generation count
    :type max_iter: int
    :param tournament_size: group size of tournament selection
    :type tournament_size: int
    :param tournament_winner_count: count of tournament winner individuals which survive one generation and reproduce.
    :type tournament_winner_count: int
    """
    # plot results
    runs = [result[0] for result in results]
    max_fitness = [result[3] for result in results]
    mean_fitness = [result[2] for result in results]
    plt.plot(runs, max_fitness, label='max')
    plt.plot(runs, mean_fitness, label='mean')
    plt.title('Fitness over generations')
    plt.xlabel('Generation')
    plt.ylabel('Fitness (number of detected cups)')
    plt.legend()
    plt.text(0.5, 0.5, f'population size: {pop_size}\nmutation probability: {mut_prob}\nmutation rate: {mut_rate}\nmax gen: {max_iter}\ntournament size: {tournament_size}\ntournament winner: {tournament_winner_count}')
    plt.savefig(fname='ga_cups_result.png')
    plt.show()
def plot_results_pallets(results: list, pop_size: int, mut_prob: float, mut_rate: float, max_iter: int, tournament_size: int, tournament_winner_count: int):
    """
    creates a simple plot to plot results of genetic algorithm against pallet markers together with parameters.

    :param results: list of results
    :type results: list
    :param pop_size: population size
    :type pop_size: int
    :param mut_prob: mutation probability
    :type mut_prop: float
    :param mut_rate: mutation rate
    :type mut_prob: float
    :param max_iter: generation count
    :type max_iter: int
    :param tournament_size: group size of tournament selection
    :type tournament_size: int
    :param tournament_winner_count: count of tournament winner individuals which survive one generation and reproduce.
    :type tournament_winner_count: int
    """
    # plot results
    runs = [result[0] for result in results]
    max_fitness = [result[3] for result in results]
    mean_fitness = [result[2] for result in results]
    plt.plot(runs, max_fitness, label='max')
    plt.plot(runs, mean_fitness, label='mean')
    plt.title('Fitness over generations')
    plt.xlabel('Generation')
    plt.ylabel('Fitness (number of detected pallets)')
    plt.legend()
    plt.text(0.5, 0.5, f'population size: {pop_size}\nmutation probability: {mut_prob}\nmutation rate: {mut_rate}\nmax gen: {max_iter}\ntournament size: {tournament_size}\ntournament winner: {tournament_winner_count}')
    plt.savefig('ga_pallet_result.png')
    plt.show()
def run_ga_cups(pop_size: int, mut_prob: float, mut_rate: float, max_iter: int, tournament_size: int, tournament_winner_count: int):
    results = []
    # create initial population and evaluate fitness
    pop = create_population(pop_size)

    for i in tqdm(range(max_iter), desc='Running GA (cups)'):
        # evaluate fitness
        for j, individual in enumerate(pop):
            individual.fitness = evaluate_fitness_cups(individual.parameters)

        # save results
        results.append([i, pop, np.mean([individual.fitness for individual in pop]),
                        np.max([individual.fitness for individual in pop]),
                        sorted(pop, key=lambda x: x.fitness, reverse=True)[0]])

        # select fittest for recombination
        new_pop = []
        for j in range(tournament_winner_count):
            new_pop.append(tournament_selection(pop, tournament_size))
        # recombine missing individuals
        for k in range(pop_size - tournament_winner_count):
            parent1 = random.choice(new_pop)
            parent2 = random.choice(new_pop)
            new_pop.append(recombine_parameters(parent1, parent2))
        # mutate population
        for l in range(pop_size):
            new_pop[l] = mutate_parameter(new_pop[l], mut_prob, mut_rate)
        pop = new_pop
    return results
def run_ga_pallets(pop_size: int, mut_prob: float, mut_rate: float, max_iter: int, tournament_size: int, tournament_winner_count: int):
    results = []
    # create initial population and evaluate fitness
    pop = create_population(pop_size)

    for i in tqdm(range(max_iter), desc=f'Running GA (pallets)'):
        # evaluate fitness
        for j, individual in enumerate(pop):
            individual.fitness = evaluate_fitness_pallet(individual.parameters)

        # save results
        results.append([i, pop, np.mean([individual.fitness for individual in pop]),
                        np.max([individual.fitness for individual in pop]),
                        sorted(pop, key=lambda x: x.fitness, reverse=True)[0]])

        # select fittest for recombination
        new_pop = []
        for j in range(tournament_winner_count):
            new_pop.append(tournament_selection(pop, tournament_size))
        # recombine missing individuals
        for k in range(pop_size - tournament_winner_count):
            parent1 = random.choice(new_pop)
            parent2 = random.choice(new_pop)
            new_pop.append(recombine_parameters(parent1, parent2))
        # mutate population
        for l in range(pop_size):
            new_pop[l] = mutate_parameter(new_pop[l], mut_prob, mut_rate)
        pop = new_pop
    return results
def tournament_selection(population: list[Individual], tournament_size: int) -> Individual:
    """
    function to select fittest individual from tournament in population.
    tournament_size individuals are selected and the fittest individual is returned.

    :param population: population
    :type population: list[Individual]
    :param tournament_size: determines the group size out of which the fittest indivisual is selected
    :type tournament_size: int
    :returns: instance of Individual (fittest in tournament)
    """
    competitors = random.sample(population, k=tournament_size)
    fittest = sorted(competitors, key=lambda x: x.fitness, reverse=True)[0]
    return fittest


def evaluate_fitness_shelves(parameters):
    """
    Calculates fittness of an Individual object's parameters attribute by detecting shelf markers in a raw image.
    If a marker is detected (detected a valid marker ID) fitness is increased by 1.
    If an error occurs while detecting, fitness is decreased by 1.
    :param parameters: parameters attribute of Individual object
    :type parameters: cv2.aruco.DetectorParameters
    :returns points: fitness value
    :rtype: int
    """
    arucodict = cv2.aruco.getPredefinedDictionary(cv2.aruco.DICT_6X6_250)
    points = 0
    try:
        corners, ids, rejected = cv2.aruco.detectMarkers(raw_shot, arucodict, parameters=parameters)
        if ids[0] == 0:
            points += 1
    except Exception as e:
        points -= 1
    return points


def run_ga_shelves(pop_size, mut_prob, mut_rate, max_iter, tournament_size, tournament_winner_count):
    results = []
    # create initial population and evaluate fitness
    pop = create_population(pop_size)
    for i in tqdm(range(max_iter), desc=f'Running GA (shelves)'):
        # evaluate fitness
        for j, individual in enumerate(pop):
            individual.fitness = evaluate_fitness_shelves(individual.parameters)
        # save results
        results.append([i, pop, np.mean([individual.fitness for individual in pop]),
                        np.max([individual.fitness for individual in pop]),
                        sorted(pop, key=lambda x: x.fitness, reverse=True)[0]])
        # select fittest for recombination
        new_pop = []
        for j in range(tournament_winner_count):
            new_pop.append(tournament_selection(pop, tournament_size))
        # recombine missing individuals
        for k in range(pop_size - tournament_winner_count):
            parent1 = random.choice(new_pop)
            parent2 = random.choice(new_pop)
            new_pop.append(recombine_parameters(parent1, parent2))
        # mutate population
        for l in range(pop_size):
            new_pop[l] = mutate_parameter(new_pop[l], mut_prob, mut_rate)
        pop = new_pop
    return results

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
    raw_shot = cv2.imread("raw_shot.png")

    raw_shot = automatic_brightness_and_contrast(raw_shot, 1)

    cups = []
    #for i in range(18):
    #    if i in (6,7,8,12,13,14):
    #        filename = 'cup' + str(i + 1) + '.png'
    #        img = cv2.imread(filename)
    #        cups.append(img)
#
    pallets = []
    #for i in range(18):
    #    if i in (6,7,8,12,13,14):
    #        filename = 'pallet_' + str(i + 1) + '.png'
    #        img = cv2.imread(filename)
    #        pallets.append(img)

    pop_size = 50
    mut_prob = 0.05
    mut_rate = 1
    max_iter = 50
    tournament_size = 20
    tournament_winner_count = 20

    # run ga against shelves
    result_shelves = run_ga_shelves(pop_size, mut_prob, mut_rate, max_iter, tournament_size, tournament_winner_count)
    plot_results_pallets(result_shelves, pop_size, mut_prob, mut_rate, max_iter, tournament_size, tournament_winner_count)
    fittest_generation = sorted(result_shelves, key = lambda x: x[3], reverse=True)[0]
    fittest_individual = fittest_generation[4]
    dump_parameters(fittest_individual.parameters, '../data/ConfDetectionGrayCups0.yaml')
    dump_parameters(fittest_individual.parameters, '../data/ConfDetectionGrayPallets0.yaml')


    ## run ga for cups
    #results_cups = run_ga_cups(pop_size, mut_prob, mut_rate, max_iter, tournament_size, tournament_winner_count)
    #plot_results_cups(results_cups, pop_size, mut_prob, mut_rate, max_iter, tournament_size, tournament_winner_count)
    #fittest_generation = sorted(results_cups, key=lambda x: x[3], reverse=True)[0]
    #fittest_individual = fittest_generation[4]
    #dump_parameters(fittest_individual.parameters, '../data/ConfDetectionGrayCups4.yaml')
#
    ## run ga for pallets
    #results_pallets = run_ga_pallets(pop_size, mut_prob, mut_rate, max_iter, tournament_size, tournament_winner_count)
    #plot_results_pallets(results_pallets, pop_size, mut_prob, mut_rate, max_iter, tournament_size, tournament_winner_count)
    #fittest_generation = sorted(results_pallets, key=lambda x: x[3], reverse=True)[0]
    #fittest_individual = fittest_generation[4]
    #dump_parameters(fittest_individual.parameters, '../data/ConfDetectionGrayPallets4.yaml')



