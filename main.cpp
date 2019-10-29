//Ali Malik
//amalik36


#include <iostream>
#include <sstream>
#include <sstream>
#include <vector>
#include <array>
#include <cstring>
#include <cmath>
#include <utility>
//#include <tuple>
//#include "direct.h"
//#include "set.h"
//#include "full.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::log2;
using std::pair;
using std::stringstream;
//using std::tuple;

int convertDec(string a);
void direct(int offset, int index, string allocate, string write);
vector<pair<char, string>> listBins();
string convertBin(const string& bin, char a);
void set(int offset, int index, int blocks, string allocate, string write, string form);
void full(int offset, int blocks, string allocate, string write, string form);


/** Main driver function*/
int main(int argc, char *argv[]) {
	stringstream cc;
	cc << argv[3];
	int atleast_four;
	cc >> atleast_four;
	if (atleast_four < 4) {
		std::cerr << "Illegal argument";
		return 1;
	}
	
	string test1 = argv[1];
	string test = argv[2];
	if (test.compare("1") == 0) {
		stringstream ss;
		ss << argv[3] << ' ' << argv[1];
		int a;
		int b;
		ss >> a >> b;
		int offset = a;
		int index = b;
		//int offset = log2(a);
		//int index = log2(b);
		//int tag = 32 - offset - index;
		direct(offset, index, argv[4], argv[5]);

	} else if (test1.compare("1") == 0) {
		stringstream ss;
		ss << arg[2] << ' ' << arg[3];
		int a;
		int b;
		ss >> a >> b;
		int offset = b;
		int blocks = a;
		full(offset, blocks, argv[4], argv[5], argv[6]);

	} else {
		stringstream ss;
                ss << argv[3] << ' ' << argv[1] << ' ' << argv[2];
                int a;
                int b;
		int c;
                ss >> a >> b >> c;
                int offset = a;
                int index = b;
		int blocks = c;
                //int offset = log2(a);
                //int index = log2(b);
                //int tag = 32 - offset - index;
                set(offset, index, blocks, argv[4], argv[5], arg[6]);
	}
}


/** Function to deal with a set associatively mapped
 * cache. uses vector of vectors of pairs to deal with 
 * n and m sets and blocks. Takes into account each possibility 
 * of allocate, write and form so quite long.
*/
void set(int offset, int index, int blocks, string allocate, string write, string form) {
	vector<vector<pair<int, string>>> tester(index, vector<pair<int, string>>(blocks));
	
	vector<pair<char, string>> converted;
        int total_loads = 0;
        int total_stores = 0;
        int load_hits = 0;
        int load_misses = 0;
        int store_hits = 0;
        int store_misses = 0;
        int total_cycles = 0;

        int offset_bits = log2(offset);
        int index_bits = log2(index);
        int tag_bits = 32 - offset_bits - index_bits;
	int sets = index;
	int blocks_per_set = blocks;
	//bool hit == true;

	for (std::vector<std::vector<std::pair<int, std::string>>>::iterator it = tester.begin(); it != tester.end(); ++it) {
		for (std::vector<std::pair<int, std::string>>::iterator its = it->begin(); its != it->end(); ++its) {
			*its = std::make_pair(0, "");
		}
	}

	converted = listBins();
        for (std::vector<std::pair<char, std::string>>::iterator bin = converted.begin(); bin != converted.end(); ++bin) {
                char check = bin->first;
                if (check == 'l') {
                        bool hit == false;
			total_loads++;
                        string index_check = bin->second.substr(tag_bits, index_bits);
                        int check1 = convertDec(index_check);
				int set = check1 % sets;
                                vector<pair<int, string>> set = tester.at(set);
                                string tag_check = it->second.substr(0, tag_bits);
                                //int check2 = convertDec(tag_check);
                           	
			if (form.compare("lru") == 0) {
				for (std::vector<std::pair<int, std::string>>::iterator block = tester.at(set).begin(); block != tester.at(set).end(); ++block) {
                                        
					if (block->second.compare(tag_check) == 0 && block->first == 1) {
                                                total_cycles++;
                                              
                                                load_hits++;
						string first = block->second;
						int first1 = block->first;
						pair<int, string> update = std::make_pair(first1, first);
						tester.at(set).erase(block);
						tester.at(set).push_back(update);
						hit = true;
						break;
                                        } 
					if (block->second.compare("") == 0 && block->first == 0) {
                                                load_misses++;
                                                total_cycles += 101;
						string first = tag_check;
                                                int first1 = 1;
                                                pair<int, string> update = std::make_pair(first1, first);
                                                tester.at(set).erase(block);
                                                tester.at(set).push_back(update);
                                                hit = true;
                                                break;
                                        } 
					
				  }	
				  
			          if (hit != true) {
                                        load_misses++;
                                        total_cycles += 101;
                                        string first = tag_check;
                                        int first1 = 1;
                                        pair<int, string> update = std::make_pair(first1, first);
                                        tester.at(set).erase(block);
                                        tester.at(set).push_back(update);	
                                        
				      	//tester.at(check1 - 1).second = tag_check;
                                        //tester.at(check1 - 1).first = 1;
                                  }
			} else {
				for (std::vector<std::pair<int, std::string>>::iterator block = tester.at(set).begin(); block != tester.at(set).end(); ++block) {
					
					if (hit != false && block->first != 0) {
						block->first += 1;
					}
					else if (block->second.compare(tag_check) == 0 && block->first > 0) {
						total_cycles++;
						load_hits++;
						block->first += 1;
						hit = true;
					} else (block->second.compare("") == 0 && block->first == 0) {
						load_misses++;
						total_cycles += 101;
						block->first = tag_check;
						block->second = 1;
						hit = true;
					} 
					
					
				}
				
				if (hit == false) {
					int max = 0;
					for (std::vector<std::pair<int, std::string>>::iterator block = tester.at(set).begin(); block != tester.at(set).end(); ++block) {
						if (block->first > max) {
							max = block->first;
						}
					}
					for (std::vector<std::pair<int, std::string>>::iterator block = tester.at(set).begin(); block != tester.at(set).end(); ++block) {
                                                if (block->first ==  max) {
                                                        break;
                                                }
                                        }
					load_misses++;
                                        total_cycles += 101;
                                        string first = tag_check;
                                        int first1 = 1;
                                        pair<int, string> update = std::make_pair(first1, first);
                                        tester.at(set).erase(block);
                                        tester.at(set).push_back(update);
				}	
			}

		}
		else if (check == 's') {
			bool hit == false;
			total_stores++;
                        string index_check = bin->second.substr(tag_bits, index_bits);
                        int check1 = convertDec(index_check);
                                int set = check1 % sets;
                                vector<pair<int, string>> set = tester.at(set);
                                string tag_check = it->second.substr(0, tag_bits);
				
				if (write.compare("write-back") == 0) {
					if (allocate.compare("no-write-allocate") == 0) {
						std::cerr << "Incorrect combination";
						return;
					}
					if (allocate.compare("write-allocate") != 0) {
						std::cerr << "Incorrect argument";
						return;
					}
					if (form.compare("lru") == 0) {
                        	        for (std::vector<std::pair<int, std::string>>::iterator block = tester.at(set).begin(); block != tester.at(set).end(); ++block) {
				
                                        if (block->second.compare(tag_check) == 0 && block->first == 1) {
                                                total_cycles++;

                                                store_hits++;
                                                string first = block->second;
                                                int first1 = block->first;
                                                pair<int, string> update = std::make_pair(first1, first);
                                                tester.at(set).erase(block);
                                                tester.at(set).push_back(update);
                                                hit = true;
                                                break;
                                        }
                                        if (block->second.compare("") == 0 && block->first == 0) {
                                                store_misses++;
                                                total_cycle += 101;;
                                                string first = tag_check;
                                                int first1 = 1;
                                                pair<int, string> update = std::make_pair(first1, first);
                                                tester.at(set).erase(block);
                                                tester.at(set).push_back(update);
                                                hit = true;
                                                break;
                                        }

                                  }

                                  if (hit != true) {
                                        store_misses++;
                                        total_cycles += 101;
                                        string first = tag_check;
                                        int first1 = 1;
                                        pair<int, string> update = std::make_pair(first1, first);
                                        tester.at(set).erase(block);
                                        tester.at(set).push_back(update);

                                        //tester.at(check1 - 1).second = tag_check;
                                        //tester.at(check1 - 1).first = 1;
                                  }

				} else {
                                for (std::vector<std::pair<int, std::string>>::iterator block = tester.at(set).begin(); block != tester.at(set).end(); ++block) {

                                        if (hit != false && block->first != 0) {
                                                block->first += 1;
                                        }
                                        else if (block->second.compare(tag_check) == 0 && block->first > 0) {
                                                total_cycles++;
                                                store_hits++;
                                                block->first += 1;
                                                hit = true;
                                        } else (block->second.compare("") == 0 && block->first == 0) {
                                                store_misses++;
                                                total_cycles += 101;
                                                block->first = tag_check;
                                                block->second = 1;
                                                hit = true;
                                        }


                                }

                                if (hit == false) {
                                        int max = 0;
                                        for (std::vector<std::pair<int, std::string>>::iterator block = tester.at(set).begin(); block != tester.at(set).end(); ++block) {
                                                if (block->first > max) {
                                                        max = block->first;
                                                }
                                        }
                                        for (std::vector<std::pair<int, std::string>>::iterator block = tester.at(set).begin(); block != tester.at(set).end(); ++block) {
                                                if (block->first ==  max) {
                                                        break;
                                                }
                                        }
                                        store_misses++;
                                        total_cycles += 101;
                                        string first = tag_check;
                                        int first1 = 1;
                                        pair<int, string> update = std::make_pair(first1, first);
                                        tester.at(set).erase(block);
                                        tester.at(set).push_back(update);
                                }
                        }
			} else {
				if (allocate.compare("no-write-allocate") == 0) {
					if (form.compare("lru") == 0) {
					for (std::vector<std::pair<int, std::string>>::iterator block = tester.at(set).begin(); block != tester.at(set).end(); ++block) {

                                        if (block->second.compare(tag_check) == 0 && block->first == 1) {
                                                total_cycles++;

                                                store_hits++;
                                                string first = block->second;
                                                int first1 = block->first;
                                                pair<int, string> update = std::make_pair(first1, first);
                                                tester.at(set).erase(block);
                                                tester.at(set).push_back(update);
                                                hit = true;
                                                break;
                                        }
                                        if (block->second.compare("") == 0 && block->first == 0) {
                                                store_misses++;
                                                total_cycle += 100;
                                                /**string first = tag_check;
                                                int first1 = 1;
                                                pair<int, string> update = std::make_pair(first1, first);
                                                tester.at(set).erase(block);
                                                tester.at(set).push_back(update);*/
                                                hit = true;
                                                break;
                                        }

                                  }

                                  if (hit != true) {
                                        store_misses++;
                                        total_cycles += 100;
                                        /**string first = tag_check;
                                        int first1 = 1;
                                        pair<int, string> update = std::make_pair(first1, first);
                                        tester.at(set).erase(block);
                                        tester.at(set).push_back(update);*/

                                        //tester.at(check1 - 1).second = tag_check;
                                        //tester.at(check1 - 1).first = 1;
                                  }

					

				} else {
					for (std::vector<std::pair<int, std::string>>::iterator block = tester.at(set).begin(); block != tester.at(set).end(); ++block) {

                                        if (hit != false && block->first != 0) {
                                                block->first += 1;
                                        }
                                        else if (block->second.compare(tag_check) == 0 && block->first > 0) {
                                                total_cycles++;
                                                store_hits++;
                                                block->first += 1;
                                                hit = true;
                                        } else (block->second.compare("") == 0 && block->first == 0) {
                                                store_misses++;
                                                total_cycles += 100;
                                                /**block->first = tag_check;
                                                block->second = 1;*/
                                                hit = true;
                                        }


                                }

                                if (hit == false) {
                                        /**int max = 0;
                                        for (std::vector<std::pair<int, std::string>>::iterator block = tester.at(set).begin(); block != tester.at(set).end(); ++block) {
                                                if (block->first > max) {
                                                        max = block->first;
                                                }
                                        }
                                        for (std::vector<std::pair<int, std::string>>::iterator block = tester.at(set).begin(); block != tester.at(set).end(); ++block) {
                                                if (block->first ==  max) {
                                                        break;
                                                }
                                        }*/
                                        store_misses++;
                                        total_cycles += 101;
                                        /**string first = tag_check;
                                        int first1 = 1;
                                        pair<int, string> update = std::make_pair(first1, first);
                                        tester.at(set).erase(block);
                                        tester.at(set).push_back(update);*/
                                }

				}
				} else {
					if (form.compare("lru") == 0) {
                                        for (std::vector<std::pair<int, std::string>>::iterator block = tester.at(set).begin(); block != tester.at(set).end(); ++block) {

                                        if (block->second.compare(tag_check) == 0 && block->first == 1) {
                                                total_cycles++;

                                                store_hits++;
                                                string first = block->second;
                                                int first1 = block->first;
                                                pair<int, string> update = std::make_pair(first1, first);
                                                tester.at(set).erase(block);
                                                tester.at(set).push_back(update);
                                                hit = true;
                                                break;
                                        }
                                        if (block->second.compare("") == 0 && block->first == 0) {
                                                store_misses++;
                                                total_cycle += 101;
                                                string first = tag_check;
                                                int first1 = 1;
                                                pair<int, string> update = std::make_pair(first1, first);
                                                tester.at(set).erase(block);
                                                tester.at(set).push_back(update);
                                                hit = true;
                                                break;
                                        }

                                  }

                                  if (hit != true) {
                                        store_misses++;
                                        total_cycles += 100;
                                        string first = tag_check;
                                        int first1 = 1;
                                        pair<int, string> update = std::make_pair(first1, first);
                                        tester.at(set).erase(block);
                                        tester.at(set).push_back(update);

                                        //tester.at(check1 - 1).second = tag_check;
                                        //tester.at(check1 - 1).first = 1;
                                  }



                                } else {
					for (std::vector<std::pair<int, std::string>>::iterator block = tester.at(set).begin(); block != tester.at(set).end(); ++block) {

                                        if (hit != false && block->first != 0) {
                                                block->first += 1;
                                        }
                                        else if (block->second.compare(tag_check) == 0 && block->first > 0) {
                                                total_cycles++;
                                                store_hits++;
                                                block->first += 1;
                                                hit = true;
                                        } else (block->second.compare("") == 0 && block->first == 0) {
                                                store_misses++;
                                                total_cycles += 101;
                                                block->first = tag_check;
                                                block->second = 1;
                                                hit = true;
                                        }


                                }

                                if (hit == false) {
                                        int max = 0;
                                        for (std::vector<std::pair<int, std::string>>::iterator block = tester.at(set).begin(); block != tester.at(set).end(); ++block) {
                                                if (block->first > max) {
                                                        max = block->first;
                                                }
                                        }
                                        for (std::vector<std::pair<int, std::string>>::iterator block = tester.at(set).begin(); block != tester.at(set).end(); ++block) {
                                                if (block->first ==  max) {
                                                        break;
                                                }
                                        }
                                        store_misses++;
                                        total_cycles += 101;
                                        string first = tag_check;
                                        int first1 = 1;
                                        pair<int, string> update = std::make_pair(first1, first);
                                        tester.at(set).erase(block);
                                        tester.at(set).push_back(update);
                                }

				}
				}
			} else {
				std::cerr << "Illegal Argument";
				return;
			}
				
			
			
			
/** Function to deal with direct mapped cache using 
 * helper functions. Uses vector of pairs to hold cache
 * and has differences for load and store calls
*/			
			
void direct(int offset, int index, string allocate, string write) {
	vector<pair<int, string>> tester(index);

        vector<pair<char, string>> converted;
        int total_loads = 0;
        int total_stores = 0;
        int load_hits = 0;
        int load_misses = 0;
        int store_hits = 0;
        int store_misses = 0;
        int total_cycles = 0;

        int offset_bits = log2(offset);
        int index_bits = log2(index);
        int tag_bits = 32 - offset_bits - index_bits;
        //int sets = index;
        //int blocks_per_set = blocks;
        //bool hit == true;

        for (std::vector<std::pair<int, std::string>>::iterator it = tester.begin(); it != tester.end(); ++it) {
                        it->first = 0;
			it->second = "";
                
        }
	

	converted = listBins();
        for (std::vector<std::pair<char, std::string>>::iterator bin = converted.begin(); bin != converted.end(); ++bin) {
                char check = bin->first;
                if (check == 'l') {
                        //bool hit == false;
                        total_loads++;
                        string index_check = bin->second.substr(tag_bits, index_bits);
                        int check1 = convertDec(index_check);
                               
                                pair<int, string>> block = tester.at(check1-1);
                                string tag_check = it->second.substr(0, tag_bits);
                                //int check2 = convertDec(tag_check);
				
				if (block.second.compare(tag_check) == 0 && block.first == 1) {
					total_cycles++;
					load_hits++;
				} else if (block.second.compare(tag_check) != 0 && block.first == 1) {
					load_misses++;
					total_cycles += 101;
					
					tester.at(check-1).second = tag_check;
				} else {
					load_misses++;
					total_cycles += 101;
					tester.at(check - 1).first = 1;
					tester.at(check - 1).second = tag_check;
				}
		 } else if (check = 's') {
			 
			 total_stores++;
                         string index_check = bin->second.substr(tag_bits, index_bits);
                         int check1 = convertDec(index_check);

                         pair<int, string>> block = tester.at(check1-1);
                         string tag_check = it->second.substr(0, tag_bits);
			 if (write.compare("write-back") == 0) {
				 
				 if (allocate.compare("no-write-allocate") == 0) {
					 std::cerr << "Illegal combination";
					 return;
				 }
				 if (allocate.compare("write-allocate") != 0) {
					 std::cerr << "Illegal argument";
					 return;
				 }

				if (block.second.compare(tag_check) == 0 && block.first == 1) {
                                        total_cycles++;
                                        store_hits++;
                                } else if (block.second.compare(tag_check) != 0 && block.first == 1) {
                                        store_misses++;
                                        total_cycles += 101;
                                        
                                        tester.at(check-1).second = tag_check;
                                } else {
                                        store_misses++;
                                        total_cycles += 1;
                                        tester.at(check - 1).first = 1;
                                        tester.at(check - 1).second = tag_check;
                                }

			} else if (write.compare("write-through") == 0) {
				if (allocate.compare("no-write-allocate") == 0) {
                                                if (block.second.compare(tag_check) == 0 && block.first == 1) {
                                                        total_cycles += 1;
                                                        store_hits++;
                                                 } else if (block.second.compare(tag_check) != 0 && block.first == 1) {
                                                        store_misses++;
                                                        total_cycles += 100;
                                                        //tester.at(check1 - 1).second = tag_check;
                                                 } else {
                                                        store_misses++;
                                                        total_cycles += 100;
                                                        //tester.at(check1 - 1).second = tag_check;
                                                        //tester.at(check1 - 1).first = 1;
                                                 }

                                }

                                 if (allocate.compare("write-allocate") == 0) {  


                                                if (block.second.compare(tag_check) == 0 && block.first == 1) {

                                                        total_cycles += 1;
                                                        store_hits++;
                                                } else if (block.second.compare(tag_check) != 0 && block.first == 1) {
                                                        store_misses++;
                                                        total_cycles += 101;
                                                        tester.at(check1 - 1).second = tag_check;
                                                 } else {
                                                        store_misses++;
                                                        total_cycles += 101;
                                                        tester.at(check1 - 1).second = tag_check;
                                                        tester.at(check1 - 1).first = 1;
                                                 }
                                  }
                           } else {
                                  std::cerr << "Illegal argument";
                                  return;
                           }

                }
        }

}

/**Start of function for 
 * fully set associative cache types
 * param: offset, blocks, allocate, write, form
 * return: void
*/


void full(int offset, int blocks, string allocate, string write, string form) {
	vector<pair<int, string>> tester(blocks);

        vector<pair<char, string>> converted;
        int total_loads = 0;
        int total_stores = 0;
        int load_hits = 0;
        int load_misses = 0;
        int store_hits = 0;
        int store_misses = 0;
        int total_cycles = 0;

        int offset_bits = log2(offset);
        //int index_bits = log2(index);
        int tag_bits = 32 - offset_bits;

	for (std::vector<std::pair<int, std::string>>::iterator it = tester.begin(); it != tester.end(); ++it) {
		it->first = 0;
		it->second = "";
	}

	converted = listBins();
        for (std::vector<std::pair<char, std::string>>::iterator bin = converted.begin(); bin != converted.end(); ++bin) {
                char check = bin->first;
                if (check == 'l') {
                        bool hit == false;
                        total_loads++;
                        string tag_check = bin->second.substr(0, tag_bits);
                        if (form.compare("lru") == 0) {
				for (std::vector<std::pair<int, std::string>>::iterator block = tester.begin(); block != tester.end(); ++block) {
					if (block->second.compare(tag_check) == 0 && block->first == 1) {
                                                total_cycles++;

                                                load_hits++;
                                                string first = block->second;
                                                int first1 = block->first;
                                                pair<int, string> update = std::make_pair(first1, first);
                                                tester.at(set).erase(block);
                                                tester.at(set).push_back(update);
                                                hit = true;
                                                break;
                                        }
                                        if (block->second.compare("") == 0 && block->first == 0) {
                                                load_misses++;
                                                total_cycles += 101;
                                                string first = tag_check;
                                                int first1 = 1;
                                                pair<int, string> update = std::make_pair(first1, first);
                                                tester.at(set).erase(block);
                                                tester.at(set).push_back(update);
                                                hit = true;
                                                break;
                                        }

                                  }

                                  if (hit != true) {
                                        load_misses++;
                                        total_cycles += 101;
                                        string first = tag_check;
                                        int first1 = 1;
                                        pair<int, string> update = std::make_pair(first1, first);
                                        tester.at(set).erase(block);
                                        tester.at(set).push_back(update);

                                        //tester.at(check1 - 1).second = tag_check;
                                        //tester.at(check1 - 1).first = 1;
                                  }

				}
			}



}
			


/** Start of fundtion to convert
 * a string of binary to decimal
 * format
 * param: binary string
*/
int convertDec(string a) {
	long long num = std::stoll (a,0,0);
	int dec = 0;
	int base = 1;

	while(num) {
		int next = num % 10;
		num = num/10;
		dec += next * base;
		base = base * 2;
	}
	return dec;
}



/** Function to return a binary string 
 * of hex value inserted for each line 
 * in input
*/
vector<pair<char, string>> listBins() {
	vector<pair<char, string>> address;
	string check;
	while (getline(cin, check)) {
		string bin = "";
		for (int i = 4; i < 12; i++) {
			bin = convertBin(bin, check.at(i));
		}
		pair<char, string> add = make_pair(check.at(0), bin);
		address.push_back(add);
	}	
	return address;

}


/** Function to associate each hex letter
 * with the corresponding binary representation
 */
string convertBin(const string& bin, char a) {
	string conv;
	switch (a) {
		case '0':
			conv = "0000";
			return bin + conv;
			break;
		case '1':
			conv = "0001";
			return bin + conv;
			break;
		case '2':
			conv = "0010";
			return bin + conv;
			break;
		case '3':
			conv = "0011";
			return bin + conv;
			break;
		case '4':
                        conv = "0100";
                        return bin + conv;
                        break;
                case '5':
                        conv = "0101";
                        return bin + conv;
                        break;
                case '6':
                        conv = "0110";
                        return bin + conv;
                        break;
                case '7':
                        conv = "0111";
                        return bin + conv;
                        break;
		case '8':
                        conv = "1000";
                        return bin + conv;
                        break;
                case '9':
                        conv = "1001";  
                        return bin + conv;
                        break;
		case 'A':
		case 'a':
                        conv = "1010";  
                        return bin + conv;
                        break;
		case 'B':
		case 'b':
                        conv = "1011";  
                        return bin + conv;
                        break;
		case 'C':
		case 'c':
                        conv = "1100";
                        return bin + conv;
                        break;
		case 'D':
		case 'd':
                        conv = "1101";
                        return bin + conv;
                        break;
		case 'E':
		case 'e':
                        conv = "1110";
                        return bin + conv;
                        break;
		case 'F':
		case 'f':
                        conv = "1111";
                        return bin + conv;
                        break;
		default:
			break;

	}
}
