FROM python:3.12-slim

ENV PYTHONDONTWRITEBYTECODE=1 \
    PYTHONUNBUFFERED=1

WORKDIR /app
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

COPY app.py .
COPY static ./static

# Executa sem privilegios de root
RUN useradd --system --no-create-home appuser
USER appuser

EXPOSE 5000
CMD ["gunicorn", "--preload", "-w", "2", "-b", "0.0.0.0:5000", "--access-logfile", "-", "app:app"]