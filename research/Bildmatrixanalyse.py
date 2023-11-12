import numpy as np
from matplotlib import pyplot as plt
from scipy.optimize import curve_fit
import cv2
cup6 = cv2.imread("C:/Users/pink_/Documents/GitHub/muPlant_WarehouseManagement/research/Bilder/cups/cup6.png")

# Cut image to interesting size
width = cup6.shape[1]
height = cup6.shape[0]
cup6 = cup6[height//3+10 : int(2.5*height//3-10), width//3 + 15 : 2*width//3-22]

# Apply threshold
cup6 = cv2.threshold(cup6, 244, 255, cv2.THRESH_BINARY)[1]

# Manual fittet values for the bitmatrix
horizontals = np.array([7, 16, 24, 32, 40, 48, 56, 64, 72], dtype=int)
verticals = np.array([3, 9, 15, 22, 29, 37, 45, 54, 63], dtype=int)

# Create bit list and labels
bits = np.linspace(0,len(horizontals)-1, len(horizontals), dtype=int)
bitlabels = [str(x) for x in bits]

# Calculate delta values for x and y axis
deltah = [0]
deltav = [0]

blue, color_blue = [31, 130, 178], (31/255, 130/255, 178/255)
grey, color_grey = [96, 125, 139], (96/255, 125/255, 139/255)
black = [0, 0, 0]

for i in range(len(horizontals)-1):
    deltah.append(horizontals[i+1] - horizontals[i])
for i in range(len(verticals)-1):
    deltav.append(verticals[i+1] - verticals[i])

# Draw horizontal and vertical lines
for i in horizontals:
    for j in range(cup6.shape[1]):
        if all(cup6[i, j] == black):
            pass
        else:
            cup6[i, j] = blue

for i in verticals:
    for j in range(cup6.shape[0]):
        if all(cup6[j, i] == black):
            pass
        else:
            cup6[j, i] = grey

# Function of a second degree polynomial
def poly2(x, a, b, c):
    return a*x**2 + b*x + c

# function of a first degree polynomial
def poly1(x, a, b):
    return a*x + b

# Fit polynomials to data
a, b, c = curve_fit(poly2, bits, verticals)[0]
d, e = curve_fit(poly1, bits, horizontals)[0]
f, g = curve_fit(poly1, bits[1:-1], deltah[1:-1])[0]
i, j = curve_fit(poly1, bits[1:-1], deltav[1:-1])[0]

# Calculate Mean Squared Error
rmse_p1 = np.sqrt(np.mean((poly2(bits, a, b, c) - verticals)**2))
rmse_p2= np.sqrt(np.mean((poly1(bits, d, e) - horizontals)**2))
rmse_p3 = np.sqrt(np.mean((poly1(bits[1:-1], f, g) - deltah[1:-1])**2))
rmse_p4 = np.sqrt(np.mean((poly1(bits[1:-1], i, j) - deltav[1:-1])**2))


# Render data as plot
cupfig, cupax = plt.subplots(1, 3, figsize=(20, 10))
cupax[0].imshow(cup6)
cupax[0].set_title("L6 mit Bitmatrix")
cupax[0].title.set_fontsize(9)
cupax[0].tick_params(axis='both', which='major', labelsize=8)
cupax[0].set_ylabel("y")
cupax[0].set_xlabel("x")

l = "horizontale Linien"
cupax[1].plot(bits, horizontals, 'o', label=l, color=color_blue)
l = rf"$y(n_{{Bit}})={round(d,3)}\cdot n_{{Bit}} + "
l +=rf"{round(e,3)},R_{{MSE}}={round(rmse_p2,3)}$"
cupax[1].plot(bits, poly1(bits, d, e), label=l, color=color_blue)
l = "vertikale Linien"
cupax[1].plot(bits, verticals, 'x', label=l, color=color_grey)
l = rf"$x(n_{{Bit}})={round(a,3)}\cdot n_{{Bit}}^2 + {round(b,3)}"
l += rf"\cdot n_{{Bit}} + {round(c,3)}, R_{{MSE}}={round(rmse_p1,3)}$"
cupax[1].plot(bits, poly2(bits, a, b, c), label=l, color=color_grey)
cupax[1].set_xticks(bits)
cupax[1].set_xticklabels(bitlabels)
cupax[1].legend()
cupax[1].tick_params(axis='both', which='major', labelsize=8)
cupax[1].set_ylabel("y")
cupax[1].set_xlabel(r"$n_{Bit}$")
cupax[1].set_title("Orte der Bitgrenzen")
cupax[1].title.set_fontsize(9)

cupax[2].plot(bits, deltah, 'o', label=r"$\Delta y$", color=color_blue)
l= rf"$\Delta y(n_{{Bit}})={round(f,3)}\cdot n_{{Bit}}+"
l+= rf"{round(g,3)}, R_{{MSE}}={round(rmse_p3,3)}$"
cupax[2].plot(bits, poly1(bits, f, g), label=l, color=color_blue)
cupax[2].plot(bits, deltav, 'x', label=r"$\Delta x$", color=color_grey)
l = rf"$\Delta x(n_{{Bit}})={round(i,3)}\cdot n_{{Bit}}+ "
l += rf"{round(j,3)}, R_{{MSE}}={round(rmse_p4,3)}$"
cupax[2].plot(bits, poly1(bits, i, j), label=, color=color_grey)
cupax[2].set_xticks(bits)
cupax[2].set_xticklabels(bitlabels)
cupax[2].tick_params(axis='both', which='major', labelsize=8)
cupax[2].set_ylabel(r"$\Delta y$")
cupax[2].set_xlabel(r"$n_{Bit}$")
cupax[2].set_title(r"$\Delta y$/$\Delta x$ der Bitgrenzen")
cupax[2].title.set_fontsize(9)
cupax[2].legend()

# Save and show figure
cupfig.suptitle("Analyse der Bitmatrix am verzerrten Marker")
plt.savefig("C:/Users/pink_/Documents/GitHub/muPlant_WarehouseManagement/research/Bilder/cups/cup6_analyse.png", dpi=600, bbox_inches='tight')
plt.show()