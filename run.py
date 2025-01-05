import subprocess
import sys
import matplotlib.pyplot as plt


bin_path = "./tlb"
num_trials = int(sys.argv[1])
powers = int(sys.argv[2])

print("We are running {} trials up to {} pages".format(num_trials, 2**powers))

# start from 2 and go up by powers of 2 to 1028 pages
num_pages = 2

x = []
y = []

for i in range(powers):
    result = subprocess.run(
        [bin_path, str(num_trials), str(num_pages)], capture_output=True
    )
    x.append(int(num_pages))
    y.append(float(result.stdout.decode()))
    num_pages *= 2

plt.plot(x, y, marker="o")

plt.xticks(x, x, fontsize="small")
plt.xlabel("Number of pages")
plt.ylabel("Nanoseconds per access")

plt.savefig("graph.png")

plt.close()

subprocess.run(["gio", "open", "graph.png"])
