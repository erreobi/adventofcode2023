import sys

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


def main():
    nome_file = sys.argv[1]  # Sostituisci con il nome del tuo file
    testo = leggi_file(nome_file)
    print(testo)

    sequences = testo.split(',')
    tot = 0
    for seq in sequences:
        hash_seq = calculateHash(seq)
        print(f'risultato: {seq} -> {calculateHash(seq)}')
        tot += hash_seq

    print(f'tot: {tot}')

if __name__ == "__main__":
   main()
