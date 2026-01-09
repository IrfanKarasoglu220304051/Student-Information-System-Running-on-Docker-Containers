# Student Information System

A Docker-based C++ + PostgreSQL Student Information System developed as a System Programming course project.

---

## Project Purpose

This project aims to demonstrate:

- C++ application development with a clean structure
- PostgreSQL database integration using libpqxx
- Containerized development using Docker and Docker Compose
- Team-based workflow using GitHub Flow
- Continuous Integration using GitHub Actions
- Clear documentation with week-based progress tracking

---

## Architecture Overview

The system consists of three main components:

### 1. C++ Application
- Implements all business logic
- Provides full CRUD operations
- Connects to PostgreSQL using libpqxx
- Built using CMake
- Runs inside a Docker container

### 2. PostgreSQL Database
- Stores student, course, and enrollment data
- Automatically initialized using schema.sql
- Runs in a separate Docker container
- Uses a persistent Docker volume

### 3. Docker Compose
- Orchestrates application and database containers
- Provides isolated networking
- Manages environment variables
- Ensures reproducible setup across systems

---

## Repository Structure

.
├── .github/workflows/ci.yml
├── include/
├── src/
├── test/
├── docs/
├── Dockerfile
├── Dockerfile.db
├── docker-compose.yml
├── CMakeLists.txt
├── schema.sql
├── sample_data.sql
├── .env.example
└── README.md

---

## Environment Variables

The application uses the following environment variables:

- DB_HOST (default: db)
- DB_PORT (default: 5432)
- DB_NAME (default: studentdb)
- DB_USER
- DB_PASSWORD

An example configuration is provided in .env.example.

---

## How to Run the Project

### Requirements
- Docker
- Docker Compose (v2 recommended)

### Recommended First-Time Setup

docker compose down -v
docker compose up -d --build

This ensures:
- Containers are rebuilt
- Database schema is applied
- Volumes are initialized cleanly

---

## Validation & Smoke Test

### Check running containers
docker compose ps

### Check application logs
docker compose logs --tail=200 app

### Verify database tables
docker exec -it postgres_db psql -U student -d studentdb -c "\dt"

Smoke Test Result:
- Application starts without crashing
- PostgreSQL connection is successfully established
- Verified manually using Docker Compose

---

## Continuous Integration (CI)

CI is implemented using GitHub Actions.

### CI Capabilities
- Runs on pull requests to develop
- Builds the C++ application using CMake
- Verifies Docker images build successfully

Workflow location:
.github/workflows/ci.yml

---

## Branching Strategy

- main → Stable
- develop → Active development
- feature/* → Feature branches
- backup/* → Backup branches

All changes are merged into develop via Pull Requests.

---

## Weekly Progress

### Week 1 – Project Setup
- Repository initialized
- Branching strategy defined
- Docker Compose skeleton created
- .env.example added
- Initial documentation prepared

### Week 2 – Build & Dockerization
- CMake build system configured
- Dockerfile for C++ application created
- PostgreSQL Dockerfile created
- docker-compose.yml finalized
- Application built successfully inside container

### Week 3 – Database & Application Logic
- PostgreSQL schema designed
- Automatic database initialization implemented
- libpqxx integration completed
- Full CRUD operations implemented
- Input validation and error handling added

### Week 4 – CI, Testing & Finalization
- GitHub Actions CI workflow added
- C++ build verified in CI
- Docker build verified in CI
- Smoke tests executed and documented
- README reviewed and finalized
- Minor code cleanup and consistency improvements applied

---

## Current Project Status

- Core functionality completed
- CI pipeline active and passing
- Docker setup stable
- Documentation finalized
- Ready for submission

---

## Known Limitations

- CLI-based interface only
- No authentication or authorization
- No advanced automated test coverage

---

## Team

- İrfan Karaşoğlu – Project Manager
- Veysel Özaslan – Docker & DevOps
- Berkay Erdoğan – C++ Developer

---

## Final Notes

All project requirements have been implemented.
The project follows best practices for containerization, CI, and collaborative development.

