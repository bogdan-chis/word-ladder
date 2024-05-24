//#include "TestDictionary.h"
//
//void TestDictionary::testGeneratePatterns()
//{
//	std::cout << "Testing Generate Patterns... \n";
//	Dictionary d;
//	string word = "SAME";
//	vector<string> expPatterns = { "*AME","S*ME","SA*E","SAM*" };
//
//	vector <string> resultedPatterns = d.generatePatterns(word);
//
//	assert(expPatterns == resultedPatterns);
//}
//
//void TestDictionary::testAdd()
//{
//	std::cout << "Testing Add... \n";
//	Dictionary d;
//	map<string, vector<string>> expDict = {
//		{"*AME", {"SAME", "CAME", "LAME", "NAME", "FAME"}},
//		{"S*ME", {"SAME", "SOME"}},
//		{"SA*E", {"SAME","SALE", "SAGE", "SANE", "SASE"}},
//		{"SAM*", {"SAME"}},
//
//		{"C*ME", {"CAME"}},
//		{"CA*E", {"CAME"}},
//		{"CAM*", {"CAME"}},
//
//
//		{"F*ME", {"FAME"}},
//		{"FA*E", {"FAME"}},
//		{"FAM*", {"FAME"}},
//		
//		{"L*ME", {"LAME"}},
//		{"LA*E", {"LAME"}},
//		{"LAM*", {"LAME"}},
//
//		{"N*ME", {"NAME"}},
//		{"NA*E", {"NAME"}},
//		{"NAM*", {"NAME"}},
//
//		{"*OME", {"SOME"}},
//		{"SO*E", {"SOME"}},
//		{"SOM*", {"SOME"}},
//
//		{"*ALE", {"SALE"}},
//		{"S*LE", {"SALE"}},
//		{"SAL*", {"SALE"}},
//
//		{"*AGE", {"SAGE"}},
//		{"S*GE", {"SAGE"}},
//		{"SAG*", {"SAGE"}},
//
//		{"*ANE", {"SANE"}},
//		{"S*NE", {"SANE"}},
//		{"SAN*", {"SANE"}},
//
//		{"*ASE", {"SASE"}},
//		{"S*SE", {"SASE"}},
//		{"SAS*", {"SASE"}}
//	};
//
//	d.add("SAME");
//
//	d.add("CAME");
//	d.add("LAME");
//	d.add("NAME");
//	d.add("SOME");
//	
//	d.add("SALE");
//	
//	d.add("SAGE");
//	d.add("SANE");
//	d.add("SASE");
//
//	d.add("FAME");
//	
//	d.view();
//	
//	assert(expDict == d.getWords());
//}