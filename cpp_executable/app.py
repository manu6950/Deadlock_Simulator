import streamlit as st
import subprocess

st.title("Deadlock Simulator - Banker's Algorithm")

# Step 1: Number of Processes and Resources
n = st.number_input("Enter number of processes (n)", min_value=1, step=1)
m = st.number_input("Enter number of resources (m)", min_value=1, step=1)

if n and m:
    st.write("### Allocation Matrix")
    allocation = []
    for i in range(n):
        st.write(f"Process P{i}")
        row = []
        for j in range(m):
            val = st.number_input(f"Allocation of Resource R{j} to Process P{i}", min_value=0, step=1, key=f"alloc_{i}_{j}")
            row.append(val)
        allocation.append(row)

    st.write("### Max Need Matrix")
    max_need = []
    for i in range(n):
        st.write(f"Process P{i}")
        row = []
        for j in range(m):
            val = st.number_input(f"Max Need of Resource R{j} for Process P{i}", min_value=0, step=1, key=f"max_{i}_{j}")
            row.append(val)
        max_need.append(row)

    st.write("### Available Resources")
    available = []
    for j in range(m):
        val = st.number_input(f"Available instances of Resource R{j}", min_value=0, step=1, key=f"avail_{j}")
        available.append(val)

    if st.button("Run Deadlock Simulator"):
        # Create input.txt dynamically
        with open("input.txt", "w") as f:
            f.write(f"{n} {m}\n")
            for row in allocation:
                f.write(" ".join(map(str, row)) + "\n")
            for row in max_need:
                f.write(" ".join(map(str, row)) + "\n")
            f.write(" ".join(map(str, available)) + "\n")

        # Run the deadlock_simulator executable
        result = subprocess.run(["deadlock_simulator.exe", "input.txt", "output.txt"], capture_output=True, text=True)

        # Display Output
        with open("output.txt", "r") as f:
            output = f.read()

        st.text_area("Result", output, height=400)
