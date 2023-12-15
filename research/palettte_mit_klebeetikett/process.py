
import cv2

# Load the ArUco dictionary
aruco_dict = cv2.aruco.getPredefinedDictionary(cv2.aruco.DICT_6X6_250)

# Read the image
image = cv2.imread(r'C:\Lagerzelle\muPlant_WarehouseManagement\research\palettte_mit_klebeetikett\pallet_2.png')

if image is not None:

    image = cv2.GaussianBlur(image, (5, 5), 0)
    corners, ids, rejected = cv2.aruco.detectMarkers(image=image, dictionary=aruco_dict)
    cv2.aruco.drawDetectedMarkers(image, corners, ids)

    # Display or save the processed image if needed
    cv2.imshow('Processed Image', image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

else:
    print("Error: Image not loaded successfully.")
