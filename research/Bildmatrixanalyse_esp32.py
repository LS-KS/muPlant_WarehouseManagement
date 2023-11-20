import os
import numpy as np
from matplotlib import pyplot as plt
from scipy.optimize import curve_fit
import cv2

raws = []
detected = []
rawfiles = ["1_esp32.jpg", "2_esp32.jpg", "3_esp32.jpg", "4_esp32.jpg", "5_esp32.jpg"]
detection = [ "1_espImage.png", "2_espImage.png", "3_espImage.png", "4_espImage.png",  "5_espImage.png"]

for file in rawfiles:
        raws.append(cv2.imread(f"research/Bilder_esp32/{file}"))
for file in detection:
        detected.append(cv2.imread(f"research/Bilder_esp32/{file}"))

fig, axs = plt.subplots(5, 2, figsize=(10, 25))
for i in range(5):
        raws[i] = cv2.rotate(raws[i], cv2.ROTATE_90_COUNTERCLOCKWISE)
        detected[i] = np.copy(raws[i])
        corners, ids, rejected = cv2.aruco.detectMarkers(detected[i], cv2.aruco.getPredefinedDictionary(cv2.aruco.DICT_6X6_250))
        detected[i] = cv2.aruco.drawDetectedMarkers(detected[i], corners, ids)
        axs[i, 0].imshow(raws[i])
        axs[i, 1].imshow(detected[i])
        axs[i, 0].set_title(f"Raw image {i+1}")
        axs[i, 1].set_title(f"Detected image {i+1}")
        axs[i, 0].axis("off")
        axs[i, 1].axis("off")
plt.tight_layout()
plt.savefig("research/Bilder_esp32/esp32_imagesWithoutProcessing.png")

# Cut lower part of image away. 

detected_after_cut = []
for i in range(len(raws)):
        raws[i] = raws[i][0:int(0.66*len(raws[i][1])), :]
        detected_after_cut.append(np.copy(raws[i]))
        corners, ids, rejected = cv2.aruco.detectMarkers(raws[i], cv2.aruco.getPredefinedDictionary(cv2.aruco.DICT_6X6_250))
        detected_after_cut[i] = cv2.aruco.drawDetectedMarkers(detected_after_cut[i], corners, ids)

fig, axs = plt.subplots(5, 2, figsize=(10, 18))
for i in range(len(raws)):
        axs[i, 0].imshow(raws[i])
        axs[i, 1].imshow(detected_after_cut[i])
        axs[i, 0].set_title(f"Raw image {i+1}")
        axs[i, 1].set_title(f"Detected image {i+1}")
        axs[i, 0].axis("off")
        axs[i, 1].axis("off")
plt.tight_layout()
plt.savefig("research/Bilder_esp32/esp32_imagesAfterCut.png")

