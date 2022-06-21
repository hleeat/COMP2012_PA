#include "signatures.h"
#include "number.h"

SigType Signature::GetType() const
{
    string name = typeid(*this).name();

    if (name == "12DSASignature")
        return DSA;
    else if (name == "16SchnorrSignature")
        return Schnorr;
    else
        throw invalid_argument("Signature Type does not exist!");
}
Signature::Signature() {}
Signature::~Signature()
{
}
SchnorrSignature::~SchnorrSignature()
{
    cout << "Destruct SchnorrSignature..." << endl;
    delete s;
    delete e;
}
DSASignature::~DSASignature()
{
    cout << "Destruct DSASignature..." << endl;
    delete r;
    delete s;
}
PublicKey::PublicKey() {}
PublicKey::~PublicKey()
{
}
SchnorrPublicKey::~SchnorrPublicKey()
{
    cout << "Destruct SchnorrPublicKey..." << endl;
    delete y;
}
DSAPublicKey::~DSAPublicKey()
{
    cout << "Destruct DSAPublicKey..." << endl;
    delete y;
}
SecretKey::SecretKey() {}
SecretKey::~SecretKey() {}
SchnorrSecretKey::~SchnorrSecretKey()
{
    cout << "Destruct SchnorrSecretKey..." << endl;
    delete x;
}
DSASecretKey::~DSASecretKey()
{
    cout << "Destruct DSASecretKey..." << endl;
    delete x;
}
//Todo: Constructors/Destructors

bool SchnorrPublicKey::Verify(const string &message, const Signature &signature) const
{
    //Todo
    int n1 = Number::NSign(Number::Sub(*(static_cast<const SchnorrSignature &>(signature).s), Number(0)));
    int n2 = Number::NSign(Number::Sub(*(static_cast<const SchnorrSignature &>(signature).s), *Number::Q));
    int n3 = Number::NSign(Number::Sub(*(static_cast<const SchnorrSignature &>(signature).e), Number(0)));
    int n4 = Number::NSign(Number::Sub(*(static_cast<const SchnorrSignature &>(signature).e), *Number::Q));
    if (n1 > 0 && n2 < 0 && n3 > 0 && n4 < 0)
    {
        Number g_s=Number::Pow(*Number::G,*(static_cast<const SchnorrSignature &>(signature).s),*Number::P);
        Number y_e=Number::Pow(*(this->y),*(static_cast<const SchnorrSignature &>(signature).e),*Number::P);
        Number r=Number::Mul_Mod(g_s,y_e,*Number::P);
        Number e_v=Number::Mod(Number::Hash(r,message),*Number::Q);
        Number temp=Number::Sub(e_v,*(static_cast<const SchnorrSignature &>(signature).e));
        int result=Number::NSign(temp);
        if(result==0) return true;
    }
    return false;
}

bool DSAPublicKey::Verify(const string &message, const Signature &signature) const
{
    //Todo
    int n1 = Number::NSign(Number::Sub(*(static_cast<const DSASignature &>(signature).r), Number(0)));
    int n2 = Number::NSign(Number::Sub(*(static_cast<const DSASignature &>(signature).r), *Number::Q));
    int n3 = Number::NSign(Number::Sub(*(static_cast<const DSASignature &>(signature).s), Number(0)));
    int n4 = Number::NSign(Number::Sub(*(static_cast<const DSASignature &>(signature).s), *Number::Q));
    if (n1 > 0 && n2 < 0 && n3 > 0 && n4 < 0)
    {
        Number temp1 = Number::Inv(*(static_cast<const DSASignature &>(signature).s), *Number::Q);
        Number temp2 = Number::Hash(message);
        Number u1 = Number::Mul_Mod(temp2, temp1, *Number::Q);
        Number u2 = Number::Mul_Mod(*(static_cast<const DSASignature &>(signature).r), temp1, *Number::Q);
        Number temp3 = Number::Pow(*Number::G, u1, *Number::P);
        Number temp4 = Number::Pow(*(this->y), u2, *Number::P);
        Number temp5 = Number::Mul_Mod(temp3, temp4, *Number::P);
        Number temp6 = Number::Mod(temp5, *Number::Q);
        Number temp7 = Number::Sub(temp6, *(static_cast<const DSASignature &>(signature).r));
        int result = Number::NSign(temp7);
        if (result == 0)
            return true;
    }
    return false;
}

const Signature *SchnorrSecretKey::Sign(const string &message) const
{
    //Todo
    while (true)
    {
        Number k = Number::Rand(1, *Number::Q);
        Number r = Number::Pow(*Number::G, k, *Number::P);
        Number e = Number::Mod(Number::Hash(r, message), *Number::Q);
        Number xe = Number::Mul_Mod(*(this->x), e, *Number::Q);
        Number s = Number::Mod(Number::Sub(k, xe), *Number::Q);

        if (Number::NSign(s) > 0 && Number::NSign(e) > 0)
            return new SchnorrSignature(new Number(s), new Number(e));
    }
}

const Signature *DSASecretKey::Sign(const string &message) const
{
    while (true)
    {
        Number k = Number::Rand(1, *Number::Q);
        Number r = Number::Mod(Number::Pow(*Number::G, k, *Number::P), *Number::Q);
        Number z = Number::Hash(message);
        Number zxr = Number::Mod(Number::Add(z, Number::Mul_Mod(*(this->x), r, *Number::Q)), *Number::Q);
        Number ki = Number::Inv(k, *Number::Q);
        Number s = Number::Mul_Mod(ki, zxr, *Number::Q);

        if (Number::NSign(r) > 0 && Number::NSign(s) > 0)
            return new DSASignature(new Number(r), new Number(s));
    }
}

SigPair::SigPair(const PublicKey *publicKey, const SecretKey *secretKey)
    : publicKey(publicKey), secretKey(secretKey)
{
}

SigPair::~SigPair()
{
    cout << "Destruct SigPair..." << endl;
    delete publicKey;
    delete secretKey;
}

const SigPair *GenerateKey(SigType sigType, const string &info)
{
    if (sigType == DSA)
    {
        Number x = Number::Rand(Number(1), *Number::Q);
        Number y = Number::Pow(*Number::G, x, *Number::P);
        const Number *newX = new Number(x);
        const Number *newY = new Number(y);

        DSASecretKey *sk = new DSASecretKey(newX);
        DSAPublicKey *pk = new DSAPublicKey(newY);

        SigPair *sigPair = new SigPair(pk, sk);

        return sigPair;
    }
    else if (sigType == Schnorr)
    {
        //Todo
        Number x = Number::Rand(Number(1), *Number::Q);
        Number y = Number::Pow(*Number::G, x, *Number::P);
        const Number *newX = new Number(x);
        const Number *newY = new Number(y);

        SchnorrSecretKey *sk = new SchnorrSecretKey(newX);
        SchnorrPublicKey *pk = new SchnorrPublicKey(newY);

        SigPair *sigPair = new SigPair(pk, sk);

        return sigPair;
    }
    return nullptr;
}

vector<SigType> SigTypes()
{
    vector<SigType> s;
    s.push_back(DSA);
    s.push_back(Schnorr);
    return s;
}
