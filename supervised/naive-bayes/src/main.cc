/*
    src/main.cc
    Written by, Sohail Qayum Malik [soni@sharingeconomy.pk]
 */

#include "../../../lib/csv/lib/sundry/cooked_read.hh"
#include "../../../lib/csv/src/parser.hh"

#include "main.h"

int main (int argc, char* argv[])
{
    cc_tokenizer::String<char> csvs;

    if (argc  < 3)
	{
		std::cout<<"Example usage: "<<argv[0]<<" <csv file1> <csv file2> [csv file3 ... nth csv file]"<<std::endl;
		return 0;
	}

    for (int i = 1; i < argc; i++)
	{		
		csvs = csvs + cc_tokenizer::String<char>(argv[i]);
	}

    cc_tokenizer::csv_parser<cc_tokenizer::String<char>, char> parser(csvs, cc_tokenizer::String<char>(".csv"));

    while (parser.go_to_next_line() != cc_tokenizer::string_character_traits<char>::eof())
    {
        while (parser.go_to_next_token() != cc_tokenizer::string_character_traits<char>::eof())
		{
            if (parser.get_current_token().size())
			{
                cc_tokenizer::String<char> csv = cooked_read<char>(argv[parser.get_current_token_number()]);
                cc_tokenizer::csv_parser<cc_tokenizer::String<char>, char> inner(csv);
                
				std::cout<<parser.get_current_token_number()<<") "<<parser.get_current_token().c_str()<<std::endl;

                inner.get_line_by_number(1);

                for (cc_tokenizer::String<char>::size_type i = 0; i < inner.get_total_number_of_tokens(); i++)
                {
                    std::cout<<"----> "<<i+1<<") "<<inner.get_token_by_number(i+1).c_str()<<std::endl;
                }
			}
        }
    }


    return 0;
}