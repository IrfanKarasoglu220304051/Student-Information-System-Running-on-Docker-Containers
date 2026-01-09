# User Manual

This document explains how to run, validate, and verify
the Student Information System after installation.

---

## Target Operating System

- Ubuntu 22.04 LTS (Jammy Jellyfish)
- Validation steps are executed via Docker containers

---

## System Overview

The system consists of:
- C++ backend application
- PostgreSQL database
- Docker Compose orchestration

The application connects to the database at startup.

---

## Running the Application

docker compose up

The application starts automatically inside the app container.

---

## Smoke Test (Manual Verification)

### Step 1: Check Container Status

docker compose ps

Expected:
- app container: running
- db container: running / healthy

---

### Step 2: Check Application Logs

docker compose logs --tail=200 app

Expected:
- No crash during startup
- Successful PostgreSQL connection

This confirms:
- Database connectivity
- Correct environment variables
- Valid Docker configuration

---

## Database Verification

docker compose exec db psql -U postgres -d student_db

Inside PostgreSQL:

\dt

Expected:
- Tables created from schema.sql are present

---

## CI Validation

The project includes a GitHub Actions CI workflow.

CI performs:
- CMake-based C++ build
- Docker image build validation

CI runs on pull requests to the develop branch.

---

## Stopping the System

docker compose down

---

## Known Limitations

- No graphical user interface
- No authentication or authorization
- Intended for educational use

---

## Project Status

The project is complete according to course requirements.
All core functionality, containerization, and CI checks are implemented.
