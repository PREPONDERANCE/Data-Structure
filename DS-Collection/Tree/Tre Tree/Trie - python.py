#!/usr/bin/env python3

class TriNode:
	def __init__(self):
		self.children = {}
		self.endOfWord = False

class Trie:
	def __init__(self):
		self.root = TriNode()
	
	def insert(self, word):
		curr = self.root
		
		for c in word:
			if c not in curr.children:
				curr.children[c] = TriNode()
			curr = curr.children[c]
		
		curr.endOfWord = True
		
	def search(self, word):
		curr = self.root
		
		for c in word:
			if c not in curr.children:
				return False
			curr = curr.children[c]
		
		return curr.endOfWord
	
	def startsWith(self, prefix):
		curr = self.root
		
		for c in prefix:
			if c not in curr.children:
				return False
			curr = curr.children[c]
		
		return True
	
	
testWords = ["apple", "ai", "a", "again", "banana", "brave"]
t = Trie()
for word in testWords:
	t.insert(word)

testSearch = ["apple", "apolo", "app", "bar"]
print([t.search(word) for word in testSearch])

testPrefix = ["app", "aga", "ba", "bra"]
print([t.startsWith(prefix) for prefix in testPrefix])