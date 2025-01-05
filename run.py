import subprocess
import matplotlib.pyplot as plt

num_trials = 10_000_000

bin_path = "./tlb"
arg1 = num_trials

# start from 2 and go up by powers of 2 to 1028 pages
num_pages = 2

x = []
y = []

for i in range(6):
    result = subprocess.run([bin_path, str(arg1), str(num_pages)], capture_output=True)
    x.append(int(num_pages))
    y.append(float(result.stdout.decode()))
    num_pages *= 2

plt.plot(x, y, marker="o")

plt.xticks(x, x, fontsize="x-small")
plt.xlabel("Number of pages")
plt.ylabel("Nanoseconds per access")

plt.savefig("graph.png")

plt.close()

subprocess.run(["gio", "open", "graph.png"])
