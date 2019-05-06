from tqdm import tqdm

public = 7554519371
private = 11331991987
e = 3

message = 32696

def mod_exp(number, e, modulus):
    result = 1
    for i in tqdm(range(e)):
        result = result*number % modulus 

    return result

encoded = mod_exp(message,e,public)
print(encoded)

decoded = mod_exp(encoded,private,public)
print(decoded)