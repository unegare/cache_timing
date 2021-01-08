#!/usr/bin/env python3

from collections import OrderedDict

import os
import yaml
from typing import List

class Experiment:
    def __init__(self, buffsize: str, duration: str):
        self.d: OrderedDict = OrderedDict({'number': 0, 'input_data': {'buffer_size': buffsize}, 'results': {'duration': duration}})

    def getDict(self) -> dict:
        return self.d


class Report:
    def __init__(self):
        self.counter: int = 0
        self.d: dict = [
                    OrderedDict({'investigation': OrderedDict({'travel_variant': 'right order', 'experiments': []})}),
                    OrderedDict({'investigation': OrderedDict({'travel_variant': 'reverse order', 'experiments': []})}),
                    OrderedDict({'investigation': OrderedDict({'travel_variant': 'random access', 'experiments': []})}),
                ]

    def addExperiment(self, exps: List[Experiment]):
        for exp in enumerate(exps):
            exp[1].getDict()['number'] = self.counter + 1
            self.d[exp[0]]['investigation']['experiments'].append({'experiment':exp[1].getDict()})
        self.counter += 1
    
    def getYaml(self) -> str:
        def represent_dict_order(s, dict_data):
            return s.represent_mapping('tag:yaml.org,2002:map', dict_data.items())
        yaml.add_representer(OrderedDict, represent_dict_order)
        return yaml.dump(self.d, default_flow_style=False)


L1=os.environ.get('L1') or 64*2**10
L3=os.environ.get('L3') or 8*2**20

with os.popen(f"env L1={L1} L3={L3} ./test.sh") as pipe:
    rep = Report()
    for line in pipe:
        arr = line.split(' ')
        rep.addExperiment([
                    Experiment(f"{int(arr[0])/1048576}mb", f"{int(arr[1])}ns"),
                    Experiment(f"{int(arr[0])/1048576}mb", f"{int(arr[2])}ns"),
                    Experiment(f"{int(arr[0])/1048576}mb", f"{int(arr[3])}ns"),
                ])
    print(rep.getYaml())
