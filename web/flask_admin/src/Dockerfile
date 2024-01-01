FROM python

WORKDIR /ctf
RUN pip install flask

ADD ./templates/ ./templates/
ADD ./app.py .
ADD ./flag.txt .

EXPOSE 8000

CMD ["python", "-b", "app.py"]