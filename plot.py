import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import uproot
# Generate random 3D points
num_points = 100
x = np.random.rand(num_points)
y = np.random.rand(num_points)
z = np.random.rand(num_points)

file = uproot.open("build/Poca_100k.root")

# Access the tree in the ROOT file
tree = file["PocaTree"]
# Get the branches from the tree
branch_names = tree.keys()
# Print branch names
print("Branches in the tree:", branch_names)

# Convert branches to NumPy arrays
x = tree["fX"].array(library="np")
y = tree["fY"].array(library="np")
z = tree["fZ"].array(library="np")
scattering = tree["fScattering"].array(library="np")

# Define colors based on the z coordinate
colors = plt.cm.viridis(z / max(z))

# Create a 3D plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Scatter plot
sc = ax.scatter(x, y, z, c=colors, marker='o')

# Add color bar which maps values to colors
colorbar = plt.colorbar(sc, ax=ax, shrink=0.5, aspect=5)
colorbar.set_label('Z Value')

# Labels
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

# Show plot
plt.show()

