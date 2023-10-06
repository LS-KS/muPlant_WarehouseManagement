import cv2
import numpy as np
from matplotlib import pyplot as plt
import random
from yaml import dump
from tqdm import tqdm

class Individual:
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
def mutate_parameter(individual: Individual, mut_prob, mut_rate) -> Individual:
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
def create_population(pop_size: int) -> list:
    population = []
    for i in range(pop_size):
        parameters = cv2.aruco.DetectorParameters()
        parameters.adaptiveThreshWinSizeMin *= int(np.ceil(np.random.rand()))
        parameters.adaptiveThreshWinSizeMax *= int(np.ceil(np.random.rand()))
        parameters.adaptiveThreshWinSizeStep *= int(np.ceil(np.random.rand()))
        parameters.adaptiveThreshConstant *= np.random.rand()
        parameters.minMarkerPerimeterRate *= np.random.rand()
        parameters.maxMarkerPerimeterRate *= np.random.rand()
        parameters.polygonalApproxAccuracyRate *= np.random.rand()
        parameters.minCornerDistanceRate *= np.random.rand()
        parameters.minDistanceToBorder *= int(np.ceil(np.random.rand()))
        parameters.minMarkerDistanceRate *= np.random.rand()
        parameters.cornerRefinementMethod *= int(np.ceil(np.random.rand()))
        parameters.cornerRefinementWinSize *= int(np.ceil(np.random.rand()))
        parameters.cornerRefinementMaxIterations *= int(np.ceil(np.random.rand()))
        parameters.cornerRefinementMinAccuracy *= np.random.rand()
        parameters.markerBorderBits *= int(np.ceil(np.random.rand()))
        parameters.perspectiveRemovePixelPerCell *= int(np.ceil(np.random.rand()))
        parameters.perspectiveRemoveIgnoredMarginPerCell *= np.random.rand()
        parameters.maxErroneousBitsInBorderRate *= np.random.rand()
        parameters.minOtsuStdDev *= np.random.rand()
        parameters.errorCorrectionRate *= np.random.rand()
        parameters.aprilTagQuadDecimate *= np.random.rand()
        parameters.aprilTagQuadSigma *= np.random.rand()
        parameters.aprilTagMinClusterPixels *= int(np.ceil(np.random.rand()))
        parameters.aprilTagMaxNmaxima *= int(np.ceil(np.random.rand()))
        parameters.aprilTagCriticalRad *= np.random.rand()
        parameters.aprilTagMaxLineFitMse *= np.random.rand()
        parameters.aprilTagMinWhiteBlackDiff *= int(np.ceil(np.random.rand()))
        parameters.aprilTagDeglitch *= int(np.ceil(np.random.rand()))
        parameters.detectInvertedMarker = random.choice([True, False])
        parameters.useAruco3Detection = random.choice([True, False])
        parameters.minSideLengthCanonicalImg *= int(np.ceil(np.random.rand()))
        parameters.minMarkerLengthRatioOriginalImg *= np.random.rand()
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
    competitors = random.sample(population, k=tournament_size)
    fittest = sorted(competitors, key=lambda x: x.fitness, reverse=True)[0]
    return fittest


if __name__ == '__main__':
    cups = []
    for i in range(18):
        filename = 'cup' + str(i + 1) + '.png'
        img = cv2.imread(filename)
        cups.append(img)

    pallets = []
    for i in range(18):
        filename = 'pallet_' + str(i + 1) + '.png'
        img = cv2.imread(filename)
        pallets.append(img)

    pop_size = 1000
    mut_prob = 0.10
    mut_rate = 0.2
    max_iter = 160
    tournament_size = 20
    tournament_winner_count = 5

    # run ga for cups
    results_cups = run_ga_cups(pop_size, mut_prob, mut_rate, max_iter, tournament_size, tournament_winner_count)
    plot_results_cups(results_cups, pop_size, mut_prob, mut_rate, max_iter, tournament_size, tournament_winner_count)
    fittest_generation = sorted(results_cups, key=lambda x: x[3], reverse=True)[0]
    fittest_individual = fittest_generation[4]
    dump_parameters(fittest_individual.parameters, 'ga_runs/run5/fittest_parameters_cups.yaml')

    # run ga for pallets
    results_pallets = run_ga_pallets(pop_size, mut_prob, mut_rate, max_iter, tournament_size, tournament_winner_count)
    plot_results_pallets(results_pallets, pop_size, mut_prob, mut_rate, max_iter, tournament_size, tournament_winner_count)
    fittest_generation = sorted(results_pallets, key=lambda x: x[3], reverse=True)[0]
    fittest_individual = fittest_generation[4]
    dump_parameters(fittest_individual.parameters, 'ga_runs/run5/fittest_parameters_pallets.yaml')


