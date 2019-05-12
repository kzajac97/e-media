from tqdm import tqdm

def mod_exp(number, e, modulus):
    result = 1
    for i in range(e):
        result = result*number % modulus 

    return result

def gcd(x,y):
    while True:
        denominator = x % y

        if denominator == 0:
            return y

        x = y
        y = denominator

def get_co_prime(phi):
    e = 2
    while e < phi:
        if gcd(e, phi) == 1:
            return e
        else:
            e += 1

    return e

if __name__ == "__main__":
    p = 383
    q = 397
    public = p * q
    e = get_co_prime( (p-1)*(q-1) )
    private = int( (1 + (2 * (p -1)*(q - 1)) / e) )

    message = [32639, 32639, 32639, 32639, 32639]
    message = [353, 299, 358, 272, 382, 256, 386, 208, 384, 144, 356, 89, 336, 26, 342, 33, 35, 75, 298, 88]

    encoded = []
    decoded = []

    for m in tqdm(message):
        encoded.append(mod_exp(m,e,public))

    for enc in tqdm(encoded):
        decoded.append(mod_exp(enc,private,public))

    print("Public",public)
    print("Private",private)
    print("Message",message)
    print("Encoded",encoded)
    print("Decoded",decoded)