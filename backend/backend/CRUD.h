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
	  static T Get(std::string email)
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
	  template <class T>
	  static bool Post(nlohmann::json object)
	  {
		  T obj;
		  return obj.Post(object);
	  }
	  template <class T>
	  static bool Put(nlohmann::json object)
	  {
		  T obj;
		  return obj.Put(object);
	  }
	  template <class T>
	  static bool Delete(int deleteID)
	  {
		  T obj;
		  return obj.Delete(deleteID);
	  }
};