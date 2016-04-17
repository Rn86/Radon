[GLOBAL InteruptDescriptorTableFlush]

InteruptDescriptorTableFlush:
    mov eax, [esp+4]
    lidt [eax]
    ret
