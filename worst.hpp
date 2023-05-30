/*
	This module was store data in a tree.
   It defines the wordSet class that can store words in a tree that represents a set. The type 
	The wordSet's don't work for words larger than MAX_LEN_WORD, and the amount of letters allowed 
	are LETTER_QUAN.
	It also defines a bunch of methods:
			- aggregate_word, delete_word; that can change the set.
			- is_word, get_words_number, get_words_l, get_words_r; that doesn't alloc new 
			memory ones finished the operation.
			- +, -, *, !, n_defined, find_subword; that create a new set.
		
	I don't make exhaustive tests to prove the correctness yet, but i will.
	More explanation in the implementation file.
   Posible boost on implementation:
      - represent the silings by a nodeWS array, this will made more easy to implement get_word_r()
        and posibly optimized some operations.
*/

#ifndef mod_worst
#define mod_worst

#include <vector>
#include <string>
#include <type_traits>

#define MAX_LEN_WORD 35
#define LETTER_QUAN 27

typedef struct nodeWordSet * nodeWS;

class WordSet{
private:
   nodeWS root;
public:
   WordSet();

   WordSet(const WordSet &);
   WordSet(WordSet &&) noexcept;
   WordSet & operator=(const WordSet &);
   WordSet & operator=(WordSet &&) noexcept;
   ~WordSet();
   
   /*
		Put the word in the WordSet. Return 0 if all was ok, return 1
		if there were a problem and the word will not be aggregated.
      Theoretically, is posible to aggregate an word while having an 
      iterator to another word in any case.
   */
   unsigned aggregate_word(const std::string &);

   /*
		Quit the word of the WordSet. Return 0 if all was ok, return 1
		if there were a problem and the word will not be deleted.
   */
   unsigned delete_word(const std::string &);

   /*
     	Return true if the word is in the WordSet, return false otherwise. 
   */
   bool is_word(const std::string &) const;

   /*
     	Return the number of the words in the WordSet.
   */
   unsigned get_words_number() const;
   
   /*
		Return a vector with the words in the utter set, in increase-lenght 
		order.
   */
   std::vector<std::string> get_words_l() const; 
   
   /*
		Return a vector with the specified number of words, taked randomly.
		The words can be repited. This method isn't yet declared as const.
   */
   std::vector<std::string> get_words_r(unsigned);
   
   /*
     	Make a WordSet with the words of both the operands.
   */
   WordSet operator+(const WordSet &) const;
   
   /*
		Make a WordSet with the elements in ws1 who were not in ws2, 
		where the operation made was ws1 - ws2.
   */
   WordSet operator-(const WordSet &) const;
   
   /*
     	Make a WordSet with the words that are in both operands.
   */
   WordSet operator*(const WordSet &) const;

   /*
     	Make a WordSet with the reversed words in the operand.
   */
   WordSet operator!() const;
   
   /*
      Make a WordSet with the words that have a length shorter than the parameter.
   */
   WordSet operator<(unsigned) const;

   /*
      Make a WordSet with the words that have a length larger than the parameter.
   */
   WordSet operator>(unsigned) const;
   
   /*
		Make a WordSet with the words who's (unsigned parameter)-th 
		letter is the defined by (char paramenter).
   */
   WordSet n_defined(unsigned char, char) const;
   
   /*
		Make a WordSet with the words that contain the parameter.
		ie.: parameter = "in" ->
      ...the WordSet would contain: "in", "inside", "minus", "principle", ...
      ...and wouldn't contain: "hello", "cry", "breath", "notion", ...
   */
   WordSet find_subword(const std::string &) const;

   /*
      The iterators are arrays of nodeWS of length MAX_LEN_WORD in where are stored 
      the exact path to reach a word. 
      
      The iterator is useless after draw on the final word. The iterator belong 
      to "output iterator" class but without beign (really) continuous.

      If a word is deleted when an iterator is pointing it, the program will fail.
      The trick is to not have an iterator while deleting a word randomly from the set,
      but is posible delete if the iterator is pointing another one.
   */
   class iterator{
		private:
			nodeWS * _nodes_;
			signed char _large_ = 0;

		public:
         /* Return a finished iterator */
         iterator();
         iterator(const WordSet &);
         iterator(const iterator &);
         iterator(iterator &&);
         iterator operator=(const iterator &);
			iterator operator=(iterator &&);
         ~iterator();

         /*
            Return the pointed word by this iterator 
         */
			std::string operator*() const;
         /*
            Return true if both iterators points the same word, in the same
            set.
         */
			bool operator==(const iterator&) const;
         /*
            Return true if this iterator is pointing "after" the last word
            in the set, false otherwise.
         */
         bool is_finished() const;

         /*
            Move forward this iterator to the next word. If the operation is used 
            when is_finished() return true, an error will ocurre.
         */
         iterator& operator++();

         friend class WordSet;
	};

   /*
      Return an iterator that points the word passed by parameter. If the word
      isn't in the set, an finished iterator will be returned.
   */
   iterator find_word(const std::string &) const;

   /*
      Quit the word of the WordSet. The iterator passed by parameter will last
      finished.
   */
   void delete_word(iterator &);
};

/*
   Return a new WordSet with the words that are find in the file represented
   by the path passed by parameter. The function checks if the path represent
   an existent file, and if not, return a empty set. If the file is not "properly 
   write"(lets say, no in an existent latin-based language) is posible that some
   words will not be recognized.
*/
WordSet from_file_to_set(const std::string &);


#endif
