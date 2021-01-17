#pragma once
#include "Transition.h";
using namespace System;

namespace Wrapper {

	public ref class WrapperClass
	{
	private:
		double price;
		array<double, 1>^deltasArray;

	public:
		WrapperClass() { price = 0; deltasArray = gcnew array<double, 1>(24); };
		void getPriceDiamondEuro(int sampleNb, double T, PnlVect* spots, PnlMat* sigma, PnlVect* mu);
		double getPrice() { return price; };
		array<double, 1>^ getDeltas() { return deltasArray; };
	};
}
