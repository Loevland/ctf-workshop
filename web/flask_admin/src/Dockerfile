FROM python

WORKDIR /ctf
RUN pip install flask

ADD ./templates/ ./templates/
ADD ./app.py .
ADD ./flag.txt .

EXPOSE 8003

CMD ["python", "-b", "app.py"]
