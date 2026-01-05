import os
import re
from pathlib import Path
path = Path(__file__).parent
os.environ["BIDICT_PATH"] = os.path.join(path,"bigram.txt")
os.environ["TRIDICT_PATH"] = os.path.join(path,"trigram.txt")

if not os.path.exists(os.environ["BIDICT_PATH"]) or not os.path.exists(os.environ["BIDICT_PATH"]):
    print("dict file not found")
    exit()

with open(os.path.join(path,"norms_ends.txt"),encoding="utf-8") as f:
    ends = f.readlines()
    ends = list(map(lambda x: x.strip(),ends))

def sentencesplitfn2(l):
    endsep = re.escape("!?.~")
    # result = re.sub(r"("+r"|".join(ends)+r")"+r"([\s"+endsep+r"])",r"\1\2| ",l)
    # result = re.sub(r"("+r"|".join(ends)+r")"+r"([\s"+endsep+r"]+)",r"\1\2| ",l).strip("|")
    l = re.sub(r"("+r"|".join(ends)+r")(\d+)",r"\1 \2",l)
    # l = re.sub(r"("+r"|".join(ends)+r")([가-힣]+)",r"\1 \2",l)
    result = re.sub(r"("+r"|".join(ends)+r")"+r"([\s"+endsep+r"]+)",r"\1\2| ",l).strip().strip("|").strip()
    stks_res = []
    for res in result.split("|"):
        res = res.strip()
        # res = res.replace("다.","다.|").replace("요.","요.|").replace("요?","요?|")
        # res = res.strip().strip("|").strip().replace("||","|").strip()
        
        res = re.sub("(다|까|요|아|냐|니)([\\.!\\?]+)",r"\1\2|",res).strip().strip("|").strip()
        for res_ in res.split("|"):
            if len(res_) <= 3 or (re.search(r"[^a-zA-Z가-힣ㄱ-ㅎ\d]+",res_) and not re.search(r"[가-힣ㄱ-ㅎa-zA-Z\d]+",res_)):
                if len(stks_res) == 0:
                    stks_res.append(res_)
                else:
                    stks_res[-1] += " " + res_
            else:
                stks_res.append(res_)
    
    return stks_res

class SentSplit2: 
    def split(self,text):
        return sentencesplitfn2(text)
from ._auto2 import *

