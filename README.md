# DLL Reversa - Hijack Demo (Uso Educacional)

Este projeto demonstra como uma DLL maliciosa pode ser utilizada para abrir uma conexão reversa com um atacante, utilizando técnicas de DLL Hijacking em ambientes Windows.

⚠️ **Este conteúdo é exclusivamente para fins educacionais e laboratoriais. Não deve ser utilizado em ambientes não autorizados.**

---

## 💡 O que essa DLL faz

- Ao ser carregada (via `rundll32`, `regsvr32` ou hijack), a DLL executa um comando PowerShell escondido.
- O PowerShell estabelece uma conexão reversa com o IP do atacante.
- Um shell interativo é aberto, permitindo execução remota de comandos.
- Pode ser utilizada em cenários de:
  - Testes de segurança
  - Análise de técnicas maliciosas
  - Demonstrações em ambientes controlados

---

## 🧠 Linguagem e ferramentas utilizadas

- Linguagem: **C++**
- Ambiente: **Visual Studio**
- APIs do Windows: `ShellExecuteExW`, `CreateThread`, `DllMain`
- Payload reverso: **PowerShell**

---

## 🚀 Como compilar

1. Abra o projeto no Visual Studio
2. Configure a arquitetura (ARM64, x64 ou x86)
3. Compile o projeto como DLL (`/LD`)
4. O arquivo final será gerado em `Debug\` ou `Release\`

---

## 🧪 Como executar

### Via `rundll32`:
```cmd
regsvr32.exe caminho\dll
rundll32.exe caminho\dll,EntryPoint
