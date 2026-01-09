FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    libpqxx-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .


RUN g++ main.cpp -o app



CMD ["./build/app"]
