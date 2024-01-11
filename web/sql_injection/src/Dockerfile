FROM python:3.10-slim-buster

WORKDIR /app

COPY ./requirements.txt /app
RUN pip install -r requirements.txt

COPY . /app

EXPOSE 8001
ENV FLASK_APP=app.py

CMD ["python", "-b", "app.py"]