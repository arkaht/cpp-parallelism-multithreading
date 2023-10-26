#pragma once

#include "random.hpp"

#define DEFINE_TALK_METHOD( name ) void talk( const std::string& text ) { _restaurant.talk( #name " " + text + "\n" ); }
