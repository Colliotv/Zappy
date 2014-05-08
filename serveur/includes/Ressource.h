#ifndef __RESSOURCE_H__
# define __RESSOURCE_H__

typedef struct sRessourceManager RessourceManager;
typedef struct sCase Case;
typedef bool (*tMsg)(Client* sender, char* parameters);

RessourceManager*
RessourceManagerAllocator(void);
struct sRessourceManager{
  /* Manager Access */
  Manager*	Manager;

  /* push msg */
  bool	(*push_msg)(struct sDialogue);
  char*		*msgType;
  tMsg		*msgTrait;

  /* Map */
  Case**	Map;
};

struct sCase{
  /* Ressource (a completer) */
  bool ressource[NRESSOURCE];
};

#endif
