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
    cc_tokenizer::String<char>::pointer* statement;
    cc_tokenizer::allocator<char> alloc_obj;

    int i;
    
    if (argc  < 3)
	{
		std::cout<<"Example usage: "<<argv[0]<<" <csv file1> <csv file2> [csv file3 ... nth csv file]"<<std::endl;
		return 0;
	}
    
    statement = (cc_tokenizer::String<char>::pointer*)alloc_obj.allocate(sizeof(cc_tokenizer::String<char>::pointer)*(argc - 1));

    for (i = 1; i < argc; i++)
	{		
		csvs = csvs + cc_tokenizer::String<char>(argv[i]);

        statement[i - 1] = alloc_obj.allocate(sizeof(cc_tokenizer::String<char>));
	}

    cc_tokenizer::csv_parser<cc_tokenizer::String<char>, char> parser(csvs, cc_tokenizer::String<char>(CSV_FILE_EXTENSION));
    
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

    std::cout<<std::endl;

    parser.reset(LINES);
    parser.reset(TOKENS);
        
    while (parser.go_to_next_line() != cc_tokenizer::string_character_traits<char>::eof())
    {    
        i = 0;
        //cc_tokenizer::String<char> foo;

        while (parser.go_to_next_token() != cc_tokenizer::string_character_traits<char>::eof())
		{            
            if (parser.get_current_token().size())
		    {
                cc_tokenizer::String<char> foo;

                //std::cout<<"P(";            
                //std::cout<<parser.get_current_token().c_str()<<"/";

                foo = ((foo + "P(") + parser.get_current_token().c_str()) + "/";

                //std::cout<<foo.c_str()<<std::endl;
                            
                cc_tokenizer::String<char> csv = cooked_read<char>(argv[parser.get_current_token_number()]);
                cc_tokenizer::csv_parser<cc_tokenizer::String<char>, char> inner(csv);

                /*while (inner.go_to_next_line() != cc_tokenizer::string_character_traits<char>::eof())            
                {*/
                inner.get_line_by_number(1);

                for (cc_tokenizer::String<char>::size_type j = 1; j <= inner.get_total_number_of_tokens(); j++)
                {
                    if (j != inner.get_total_number_of_tokens())
                    {
                        //std::cout<<inner.get_token_by_number(j).c_str()<<",";
                        foo = (foo + inner.get_token_by_number(j).c_str()) + ",";
                    }
                    else 
                    {
                        //std::cout<<inner.get_token_by_number(j).c_str()<<")\n";
                        foo = (foo + inner.get_token_by_number(j).c_str()) + ")";
                    }
                }

                /*while (inner.go_to_next_token() != cc_tokenizer::string_character_traits<char>::eof())
		        { 
                    if (inner.get_current_token().size())
			        {
                        std::cout<<inner.get_current_token().c_str()<<",";
                    }
                }*/
                /*}*/

                *((cc_tokenizer::String<char>*)(statement[i])) = foo;
            }

            i++;
        }        
    }

    for (i = 0; i < argc - 1; i ++)
    {
        std::cout<<((cc_tokenizer::String<char>*)(statement[i]))->c_str()<<std::endl;
    }

    parser.reset(LINES);
    parser.reset(TOKENS);

    while (parser.go_to_next_line() != cc_tokenizer::string_character_traits<char>::eof())
    { 
        while (parser.go_to_next_token() != cc_tokenizer::string_character_traits<char>::eof())
		{
            if (parser.get_current_token().size())
		    {
                cc_tokenizer::String<char> csv = cooked_read<char>(argv[parser.get_current_token_number()]);
                cc_tokenizer::csv_parser<cc_tokenizer::String<char>, char> inner(csv);
            }
        }
    }

    for (i = 1; i < argc; i++)
	{				
        alloc_obj.deallocate(statement[i - 1]);
	}

    return 0;
}