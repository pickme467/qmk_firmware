TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes

# Use external environment variables to pass password for su1 and root users
OPT_DEFS += -DD_ROOT="$(D_ROOT)"
OPT_DEFS += -DD_SU1="$(D_SU1)"

$(info "Private opts: "$(OPT_DEFS))
