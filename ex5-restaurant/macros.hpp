#pragma once

#define DEFINE_TALK_METHOD( name ) void talk( const std::string& text ) { std::cout << #name << ": " << text << std::endl; }
