# Use a lightweight Python base image with g++
FROM python:3.9-slim

# Install build-essential for g++
RUN apt-get update && apt-get install -y build-essential

# Set working directory
WORKDIR /app

# Copy files to container
COPY . .

# Install Python dependencies
RUN pip install -r requirements.txt

# Compile C++ code
RUN g++ deadlock_simulator.cpp -o deadlock_simulator

# Streamlit Port
ENV PORT 7860

# Run Streamlit app
CMD ["streamlit", "run", "app.py", "--server.port", "7860", "--server.address", "0.0.0.0"]
