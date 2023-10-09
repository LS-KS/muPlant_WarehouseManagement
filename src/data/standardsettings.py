from cv2 import aruco
from yaml import dump
parameters = aruco.DetectorParameters()

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
filename = "standardsettings.yaml"

for field in attribute_names:
    data = {}
    for field in attribute_names:
        data[field] = getattr(parameters, field)
    with open(filename, 'w') as file:
        dump(data, file)