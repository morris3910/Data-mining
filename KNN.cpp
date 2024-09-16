#include<iostream>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;

struct data_set{
	int pregnancies;//懷孕了幾次
	double glucose;//血液中葡萄糖濃度
	double blood_pressure;//舒張壓
	double skin_thickness;//三頭肌皮摺厚度
	double insulin;//胰島素濃度
	double BMI;//BMI
	double diabetes_function;//糖尿病函數，這個函數使用了家族糖尿病史來導出個人得糖尿病的風險值
	int age;
	int outcome;//0 無糖尿病，1 有糖尿病
};

double f1(data_set set1,data_set set2);
double f2(data_set set1,data_set set2);
double f3(data_set set1,data_set set2);
bool cmp(pair<double,int> a,pair<double,int> b);

int main()
{
	fstream file;
	vector<data_set> train_data;
	vector<pair<double,int> > distance;
	//-----------------------read file and store data in struct-----------------------------
	file.open("train_data.csv",ios::in);
	string line;
	data_set data;
	getline(file,line);//don't want the titles
	while(getline(file,line,'\n'))//read train_data.csv file
	{
		istringstream tmp_line(line);
		string str;
		while(getline(tmp_line,str,','))
		{
			data.pregnancies = atoi(str.c_str());//convert string to int and store

			if(getline(tmp_line,str,','))
				data.glucose = atof(str.c_str());//convert string to double and store

			if(getline(tmp_line,str,','))
				data.blood_pressure = atof(str.c_str());

			if(getline(tmp_line,str,','))
				data.skin_thickness = atof(str.c_str());

			if(getline(tmp_line,str,','))
				data.insulin = atof(str.c_str());

			if(getline(tmp_line,str,','))
				data.BMI = atof(str.c_str());

			if(getline(tmp_line,str,','))
				data.diabetes_function = atof(str.c_str());

			if(getline(tmp_line,str,','))
				data.age = atoi(str.c_str());

			if(getline(tmp_line,str,','))
				data.outcome = atoi(str.c_str());
		}
		train_data.push_back(data);
	}
	file.close();
	//for(int i = 0;i < train_data.size();i++)
		//cout<<train_data[i].pregnancies<<" ";
	
	//------------------------------calculate distance and sort it---------------------------
	
	pair<double,int> tmp_pair;
	//for(int i = 0;i < train_data.size();i++)
	//{
		for(int i = 1;i < train_data.size();i++)
		{
			tmp_pair = make_pair(f1(train_data[0],train_data[i]),train_data[i].outcome);
			distance.push_back(tmp_pair);
		}
	//}

	
	sort(distance.begin(), distance.end(), cmp);	
	//for(int i = 0;i < distance.size();i++)
		//cout<<distance[i].first<<" "<<distance[i].second<<endl;

	//-----------------------------finding best k value-------------------------------------
	int k;
	cout<<"enter k value : ";
	cin>>k;
	int one = 0,zero = 0;
	for(int i = 0;i < k;i++)
	{
		if(distance[i].second == 1)
			one++;
		else
			zero++;
	}
	if(one > zero)
	{
		cout<<"Outcome = 1"<<endl;
		if(train_data[0].outcome == 1)
			cout<<"Prediction success"<<endl;
		else
			cout<<"Prediction fail"<<endl;
	}
	else
	{
		cout<<"Outcome = 0"<<endl;
		if(train_data[0].outcome == 0)
			cout<<"Prediction success"<<endl;
		else
			cout<<"Prediction fail"<<endl;
	}
}

bool cmp(pair<double,int> a,pair<double,int> b)
{
	return a.first < b.first;
}

double f1(data_set set1,data_set set2)//Euclidean distance
{
	double dis = 0;
	dis += pow(set1.pregnancies - set2.pregnancies,2);
	dis += pow(set1.glucose - set2.glucose,2);
	dis += pow(set1.blood_pressure - set2.blood_pressure,2);
	dis += pow(set1.skin_thickness - set2.skin_thickness,2);
	dis += pow(set1.insulin - set2.insulin,2);
	dis += pow(set1.BMI - set2.BMI,2);
	dis += pow(set1.diabetes_function - set2.diabetes_function,2);
	dis += pow(set1.age - set2.age,2);
	return sqrt(dis);
}

double f2(data_set set1,data_set set2)//Manhattan distance
{
	return pow(f1(data_set set1,data_set set2),2);
}

double f3(data_set set1,data_set set2)//Minkowski distance
{
	double dis = 0;
	dis += pow(set1.pregnancies - set2.pregnancies,8);
	dis += pow(set1.glucose - set2.glucose,8);
	dis += pow(set1.blood_pressure - set2.blood_pressure,8);
	dis += pow(set1.skin_thickness - set2.skin_thickness,8);
	dis += pow(set1.insulin - set2.insulin,8);
	dis += pow(set1.BMI - set2.BMI,8);
	dis += pow(set1.diabetes_function - set2.diabetes_function,8);
	dis += pow(set1.age - set2.age,8);
	return pow(dis,0.125);
}

