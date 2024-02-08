import sys
import re
from collections import OrderedDict
# pattern = r'(?P<label>[a-zA-Z]+)(?P<ops>[=-])(?P<strength>\d+)?'


def leggi_file(nome_file):
    with open(nome_file, 'r') as file:
        contenuto = file.read()
    return contenuto


def calculateHash(seq):
    res = 0

    for char in seq:
        res += ord(char)
        res *= 17
        res %= 256

    return res

pattern = re.compile(r'(?P<label>[a-zA-Z]+)(?P<ops>[=-])(?P<focallength>\d+)?')

def parseSequence(sequence:str):
    match = pattern.match(sequence)
    return match.group("label"),match.group("ops"),match.group("focallength")

def stampaBoxes(boxes):
    for index, box in enumerate(boxes):
      if len(box) is not 0:
        toPrint=""
        for lens,lenght in box.items():
            toPrint+=" ["+lens+" "+lenght+"]"
        print(f"Box[{index}]: {toPrint}")

def main():
    nome_file = sys.argv[1]  # Sostituisci con il nome del tuo file
    testo = leggi_file(nome_file)
    print(testo)

    boxes=[]
    for i in range(256):
        boxes.append(OrderedDict())
    
    stampaBoxes(boxes)

    sequences = testo.split(',')
    tot = 0
    for seq in sequences:
        label,ops,fLength=parseSequence(seq)
        hash_Labwl = calculateHash(label)
        print(f"After {seq} - hash({label})={hash_Labwl}")
        if (ops == "-"):
            if (boxes[hash_Labwl].get(label) is not None):
                del(boxes[hash_Labwl][label])
        if (ops == "="):
            #if (boxes[hash_Labwl].get(label) == None):
                (boxes[hash_Labwl])[label]=fLength
            #else:
            # boxes[hash_Labwl].update(label=fLength)
        stampaBoxes(boxes)
        print()
        print()
        
    for indexBoxes in range (len(boxes)):
        for indexSlot, label in enumerate(boxes[indexBoxes]):
            totLens = (1+indexBoxes)*(indexSlot+1)*(int(boxes[indexBoxes][label]))
            print(f"{indexBoxes} -> {indexSlot} -> [{label} {boxes[indexBoxes][label]}] = {totLens}")
            tot+=totLens

    print(f'tot: {tot}')

if __name__ == "__main__":
   main()
