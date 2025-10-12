FROM python:3.12

WORKDIR /electra-web
COPY electra.js .
COPY electra.wasm .
COPY index.html .
COPY worker.js .

CMD ["python", "-m", "http.server", "1225"]
