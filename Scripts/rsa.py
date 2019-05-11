from tqdm import tqdm

def mod_exp(number, e, modulus):
    result = 1
    for i in tqdm(range(e)):
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
    p = 53
    q = 59
    public = p * q
    e = get_co_prime( (p-1)*(q-1) )
    private = int( (1 + (2 * (p -1)*(q - 1)) / e) )

    message = [1,2,3,4,5,4,5,5,4,3,4,4,2,34,4,14,1,3,2,3,3,2,141,5,15]

    encoded = []
    decoded = []

    for m in message:
        encoded.append(mod_exp(m,e,public))

    for enc in encoded:
        decoded.append( mod_exp(enc,private,public) )

    print("Public",public)
    print("Private",private)
    print("Message",message)
    print("Encoded",encoded)
    print("Decoded",decoded)