import cv2
import numpy as np
from matplotlib import pyplot as plt


def cut_to_estimated_size(dup_id, rejected):
    cup = cups[dup_id]
    for i, geom in enumerate(rejected):
        print(f"rejected geometry:\n{geom}")
        geom = geom[0]
        x_series = [x[0] for x in geom]
        y_series = [y[1] for y in geom]
        print(f"x_series: {x_series}")
        print(f"y_series: {y_series}")

def evaluate_fitness(parameters: cv2.aruco.DetectorParameters)->int:
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

def mutate_parameter(parameters: cv2.aruco.DetectorParameters, mut_prob, mut_rate)->cv2.aruco.DetectorParameters:
    for i, p in enumerate(parameters):
        if np.random.rand() < mut_prob:
            parameters[i] += np.random.rand() * mut_rate
    return parameters

if __name__ == '__main__':
    cups = []
    for i in range(18):
        filename = 'cup' + str(i+1) + '.png'
        img = cv2.imread(filename)
        cups.append(img)

    pallets = []
    for i in range(18):
        filename = 'pallet_' + str(i+1) + '.png'
        img = cv2.imread(filename)
        pallets.append(img)






