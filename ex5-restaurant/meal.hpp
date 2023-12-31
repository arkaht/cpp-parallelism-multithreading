#pragma once

#include <string>
#include <set>

namespace vkr
{
	class ingredient
	{
	public:
		ingredient( std::string name ) 
			: _name( name ) {}
		ingredient( const ingredient& target )
			: _name( target._name ) {}

		void cook() { _is_cooked = true; }

		const std::string& get_name() const { return _name; }
		bool is_cooked() const { return _is_cooked; }

		static std::string concat_as_text( std::vector<ingredient> ingredients )
		{
			std::string text;

			for ( int i = 0; i < ingredients.size(); i++ )
			{
				text += ingredients[i].get_name();
				if ( i < ingredients.size() - 1 )
				{
					text += ", ";
				}
			}

			return text;
		}
	
	private:
		std::string _name;
		bool _is_cooked = false;
	};
	using physical_ingredient = std::shared_ptr<ingredient>;

	class meal
	{
	public:
		meal() {}

		//bool has_ingredient( const ingredient& ingredient );
		void add_ingredient( const physical_ingredient& ingredient ) 
		{
			_ingredients.insert( ingredient );
		}
		int get_ingredients_count() const { return (int)_ingredients.size(); }

		/*
		 *  Eat meal for a given force, returns whenever the meal is finished
		 */
		bool eat( float force )
		{
			if ( _proportion <= 0.0f ) return true;

			_proportion = std::max( 0.0f, _proportion - force );
			return _proportion <= 0.0f;
		}
		float get_proportion() const { return _proportion; }

	private:
		std::set<physical_ingredient> _ingredients;
		float _proportion = 1.0f;

	};
	using physical_meal = std::shared_ptr<meal>;

	struct recipe
	{
		std::string name;
		std::vector<ingredient> ingredients;
	};
}