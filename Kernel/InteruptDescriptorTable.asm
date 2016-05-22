[GLOBAL RnInteruptDescriptorTableFlush]

RnInteruptDescriptorTableFlush:
    mov eax, [esp+4]
    lidt [eax]
    ret
