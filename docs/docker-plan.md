# Docker Plan (Week 1)

## Services
- db: PostgreSQL (postgres:latest)
- app: C++ CLI application (custom Dockerfile - Week 2)

## Networking
- Services communicate via Docker Compose network (app uses host "db")

## Persistence
- Named volume for PostgreSQL data

## Environment Variables
- POSTGRES_DB
- POSTGRES_USER
- POSTGRES_PASSWORD
- APP_DB_HOST=db
- APP_DB_PORT=5432
