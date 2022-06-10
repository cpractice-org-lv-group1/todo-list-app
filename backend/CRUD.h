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
};