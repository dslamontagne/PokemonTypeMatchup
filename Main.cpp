//DumbBear studios recursive Pokemon type matchups 
#include <stdio.h>
#include <vector>
#include <algorithm>

enum PokeType 
{
	Normal, 
	Fire,
	Water,
	Electric,
	Grass,
	Ice,
	Fighting,
	Poison,
	Ground,
	Flying,
	Psychic,
	Bug,
	Rock,
	Ghost,
	Dragon,
	Dark,
	Steel,
	Fairy,
	MaxTypes
};

const char* TypeString[MaxTypes] = 
{
	"Normal", "Fire", "Water", "Electric", 
	"Grass", "Ice", "Fighting", "Poison", "Ground", "Flying", "Psychic", "Bug", 
	"Rock", "Ghost", "Dragon", "Dark", "Steel", "Fairy"
};
const float TypeMatrix[MaxTypes][MaxTypes] = 
{ 
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.5, 0, 1, 1, 0.5, 1},
	{1, 0.5, 0.5, 1, 2, 2, 1, 1, 1, 1, 1, 2, 0.5, 1, 0.5, 1, 2, 0.5},
	{1, 2, 0.5, 1, 0.5, 1, 1, 1, 2, 1, 1, 1, 2, 1, 0.5, 1, 1, 1},
	{1, 1, 2, 0.5, 0.5, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0.5, 1, 1, 1},
	{1, 0.5, 2, 1, 0.5, 1, 1, 0.5, 2, 0.5, 1, 0.5, 2, 1, 0.5, 1, 0.5, 1},
	{1, 0.5, 0.5, 1, 2, 0.5, 1, 1, 2, 2, 1, 1, 1, 1, 2, 1, 0.5, 1},
	{2, 1, 1, 1, 1, 2, 1, 0.5, 1, 0.5, 0.5, 0.5, 2, 0, 1, 2, 2, 2},
	{1, 1, 1, 1, 2, 1, 1, 0.5, 0.5, 1, 1, 1, 0.5, 0.5, 1, 1, 0, 0.5},
	{1, 2, 1, 2, 0.5, 1, 1, 2, 1, 0, 1, 0.5, 2, 1, 1, 1, 2, 1},
	{1, 1, 1, 0.5, 2, 1, 2, 1, 1, 1, 1, 2, 0.5, 1, 1, 1, 0.5, 1},
	{1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 0.5, 1, 1, 1, 1, 0, 0.5, 1},
	{1, 0.5, 1, 1, 2, 1, 0.5, 0.5, 1, 0.5, 2, 1, 1, 0.5, 1, 2, 0.5, 1},
	{1, 2, 1, 1, 1, 2, 0.5, 1, 0.5, 2, 1, 2, 1, 1, 1, 1, 0.5, 1},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 0.5, 0.5, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 0.5, 2},
	{1, 1, 1, 1, 1, 1, 0.5, 1, 1, 1, 2, 1, 1, 2, 1, 0.5, 0.5, 2},
	{1, 0.5, 0.5, 0.5, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 0.5, 0.5}, 
	{1, 0.5, 1, 1, 1, 1, 2, 0.5, 1, 1, 1, 1, 1, 1, 2, 2, 0.5, 1}
};

struct TypePower
{
	PokeType Type;
	float Power;
};

float BasePowers[MaxTypes];

float FinalPowers[MaxTypes];




float CalculatePokeTypePower(int depth, PokeType type)
{
	if (depth > 0)
	{
		float sum = 0.0f;
		for (int i = 0; i < MaxTypes; ++i)
		{
			sum += TypeMatrix[type][i] * CalculatePokeTypePower(depth - 1, (PokeType)i);
		}
		float average = sum / MaxTypes;
		return average;
	}
	else
	{
		return BasePowers[type];
	}
}

bool TypePowerCompare(TypePower i, TypePower j) 
{ 
	return (i.Power < j.Power);
}

void CalculateBasePower()
{
	std::vector<TypePower> BasePowerVector;
	for (int i = 0; i < MaxTypes; i++)
	{
		float sum = 0.0f;
		for (int j = 0; j < MaxTypes; j++)
		{
			sum += TypeMatrix[i][j];
		}
		float ave = sum / MaxTypes;
		BasePowers[i] = ave;
		BasePowerVector.push_back({ (PokeType)i, BasePowers[i] });
	}	
	std::sort(BasePowerVector.begin(), BasePowerVector.end(), TypePowerCompare);
	for (int i = 0; i < MaxTypes; i++)
	{
		printf("Type %s: BasePower %f \n", TypeString[BasePowerVector[i].Type], BasePowerVector[i].Power);
	}		
}

int main(int argc, char** argv)
{
	int depth = 6;

	CalculateBasePower();

	std::vector<TypePower> FinalPowerVector;

	for (int i = 0; i < MaxTypes; i++)
	{
		FinalPowers[i] = CalculatePokeTypePower(depth, (PokeType)i);
		FinalPowerVector.push_back({(PokeType)i, FinalPowers[i] });
	}
	
	std::sort(FinalPowerVector.begin(), FinalPowerVector.end(), TypePowerCompare);
	for (int i = 0; i < MaxTypes; i++)
	{
		printf("Type %s: FinalPower %f \n", TypeString[FinalPowerVector[i].Type], FinalPowerVector[i].Power);
	}

}

