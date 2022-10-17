#include <security/pam_modules.h>
#include <stdarg.h>
#include <time.h>

#define PAM_SM_AUTH
#define MAX_V 41

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const
char **argv) {
    unsigned int ctrl;
    int retval;
    const char *name, *p;
    char *right;
    time_t mytime;
    mytime = time(0);
    srandom(mytime);
    int random_vector[4];
    random_vector[0] = random() % MAX_V + 1;
    random_vector[1] = random() % MAX_V + 1;
    random_vector[2] = random() % MAX_V + 1;
    random_vector[3] = random() % MAX_V + 1;
    retval = pam_get_user(pamh, &name, "Enter your login: ");
    {
        struct pam_conv *conv;
        struct pam_msg *pmsg[4], msg[4];
        struct pam_response *response;
        retval = pam_get_item(pamh, PAM_CONV, (const void **) &conv);
        pmsg[0] = &msg[0];
        msg[0].msg_style = PAM_PROMPT_ECHO_OFF;
        msg[0].msg = malloc(100);
        snprintf(msg[0].msg, 180, "Your vector is %d %d %d %d\n", random_vector[0], random_vector[1],
                 random_vector[2]);
        retval = conv->conv(1, (const struct pam_msg **) pmsg, &response, conv->appdata_ptr);
        int user_arr[4][4] = {{1, 1,  1,  1},
                              {1, 2,  4,  8},
                              {1, 3,  9, 27},
                              {1, 4, 16, 64}};
        int user_answer[4] = {0};
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                user_answer[i] += user_arr[i][j] * random_vector[j];
            }
        }
        right = malloc(100);
        snprintf(right, 40, "%d %d %d %d", user_answer[0] % MAX_V, user_answer[1] % MAX_V, user_answer[2] % MAX_V,
                 user_answer[3] % MAX_V);
        if (!(strcmp(right, response->resp))) {
            return PAM_SUCCESS;
        } else {
            return PAM_AUTH_ERR;
        }
    }
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    unsigned int ctrl;
    int retval;
    retval = PAM_SUCCESS;
    return retval;
}
#ifdef PAM_STATIC
struct pam_module _pam_unix_auth_modstruct = {
"pam_test",
pam_sm_authenticate,
pam_sm_setcred,
NULL,
NULL,
NULL,
NULL,
};
#endif
