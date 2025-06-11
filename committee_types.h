#ifndef GOTCHA_TYPES_H
#define GOTCHA_TYPES_H



/*!
 * The representation of a Committee action
 */
typedef struct gotcha_binding_t {
  const char *name;       //!< The name of the function being wrapped
  void *wrapper_pointer;  //!< A pointer to the wrapper function
  gotcha_wrappee_handle_t
      *function_handle;  //!< A pointer to the function being wrapped
} gotcha_binding_t;

/*!
 * The representation of an error (or success) of a Committee action
 */
typedef enum Committee_error_t {
  COMMITTEE_SUCCESS= 0,         //!< The call succeeded
  COMMITTEE_FUNCTION_NOT_FOUND,  //!< The call looked up a function which could not
                              //!< be found
  COMMITTEE_INTERNAL,            //!< Internal gotcha error
  COMMITTEEINVALID_TOOL         //!< Invalid tool name
} COMMITTEE_error_t;

#endif
