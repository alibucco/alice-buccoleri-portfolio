# AROL Customer Platform

### Conversational platform for industrial fleet management

**[Explore the source code on GitHub](https://github.com/alicebucco/arol-project-q2)**

AROL Customer Platform is an authenticated web application for AROL customer companies. It brings together machine-fleet information, operational data, service records, commercial documents and machine-specific technical manuals in one interface.

The project was developed with **Daniele Bongiovanni** for the System and Device Programming course at Politecnico di Torino.

## Project goal

The goal was to make relevant machine information easier to consult while keeping industrial data protected. Users can explore fleet and machine pages, telemetry, alarms, maintenance tickets, quotations, orders and manuals - or ask the AROL Assistant questions in natural language.

Access is organised by company and user role, so that operators, technicians and commercial users only receive the information they are authorised to see.

## A controlled AI assistant

The conversational system is designed around a custom, backend-owned orchestration layer:

1. A **Planner LLM** interprets the request and proposes authorised retrieval operations.
2. The **Operation Registry** validates typed parameters, access rules and the machine context before any action runs.
3. Specialised modules retrieve evidence from **manuals, IoT data, service records and orders**.
4. A **Composer LLM** produces an answer based only on the authorised evidence, with manual citations where relevant.

The language model never has direct access to PDFs, databases, SQL queries or internal backend functions. Security-sensitive decisions remain enforced by the backend.

## Technologies

**Frontend:** React · TypeScript · Vite

**Backend:** Python · FastAPI · Pydantic

**Data & AI:** PostgreSQL · pgvector · local RAG · OpenAI-compatible LLM API

**Deployment & testing:** Docker Compose · Playwright

## Project materials

- [Project presentation](arol-customer-platform-presentation.pdf)
- [Technical report](arol-customer-platform-report.pdf)
