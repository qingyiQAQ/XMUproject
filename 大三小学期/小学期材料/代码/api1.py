from flask import Flask, jsonify, request
from py2neo import Graph

from model.model import CountModel
from utils.data_load import getEvent, CountDataset
from utils.data_query import queryData

app = Flask(__name__)
graph = Graph('bolt://localhost:7687', auth=('neo4j', '12345678'))


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=5000)