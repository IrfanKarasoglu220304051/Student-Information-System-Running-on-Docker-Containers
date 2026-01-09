# Installation Guide

This document explains how to install and set up the
Student Information System project on a local machine.

---

## Target Operating System

- Ubuntu 22.04 LTS (Jammy Jellyfish)
- Docker-based setup is OS-independent once Docker is installed

---

## Prerequisites

The following tools must be installed:

- Git
- Docker (20+)
- Docker Compose v2

Optional (for local build without Docker):
- CMake >= 3.10
- GCC / G++ (C++17)
- libpq-dev
- libpqxx-dev

---

## Clone the Repository

git clone https://github.com/IrfanKarasoglu220304051/Student-Information-System-Running-on-Docker-Containers.git
cd Student-Information-System-Running-on-Docker-Containers

---

## Environment Configuration

Create the environment file from the template:

cp .env.example .env

Default values are sufficient for local development.

---

## Build and Run with Docker Compose

docker compose up --build

This will:
- Build the C++ application container
- Start the PostgreSQL database
- Create Docker networks and volumes

---

## Verify Installation

docker compose ps

Expected result:
- app container is running
- db container is running and healthy

---

## Stop and Cleanup

docker compose down

Remove volumes as well:

docker compose down -v

---

Installation completed successfully.
