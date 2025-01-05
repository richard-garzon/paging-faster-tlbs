import subprocess
import sys
import numpy as np
import matplotlib.pyplot as plt


bin_path = "./tlb"
num_trials = int(sys.argv[1])
powers = int(sys.argv[2])

print("We are running {} trials up to {} pages".format(num_trials, 2**powers))

x = np.arange(powers + 1)
num_pages = 2**x

y = []

for pages in num_pages:
    result = subprocess.run(
        [bin_path, str(num_trials), str(pages)], capture_output=True
    )
    y.append(float(result.stdout.decode()))

print(x)
print(y)

plt.plot(x, y, marker="o")

plt.xticks(x, num_pages, fontsize="small")
plt.xlabel("Number of pages")
plt.ylabel("Nanoseconds per access")

plt.savefig("graph.png")

plt.close()

subprocess.run(["gio", "open", "graph.png"])
