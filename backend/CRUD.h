#pragma once

static class CRUD {
	
public:
	  template <class T>
	  static T Get() 
	  {
		  T obj;
		  obj.Get();
		  return obj;
	  }
	  template <class T>
	  static T Get(string email)
	  {
		  T obj;
		  obj.Get(email);
		  return obj;
	  }
	  template <class T>
	  static T Get(int id)
	  {
		  T obj;
		  obj.Get(id);
		  return obj;
	  }
};