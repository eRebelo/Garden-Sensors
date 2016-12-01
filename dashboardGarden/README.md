Dashboard Garden - Google App Engine
==================

O Dashboard Garden é um painel demonstrativo, para visualização dos dados armazenados em nuvem (Google Cloud Platform), provenientes da leitura dos sensores de temperatura e umidade relativa do ar, e umidade do solo.

## Dashboard
- [Dashboard Garden][1]

## Freeboard
- [Dashboard][2] open source, importado e adaptado

## APIs
- [Google Cloud Platform][3]

## IDE
- [IntelliJ][4]

## Importar Dashboard
- Adicionar e configurar os widgets a serem exibidos pelo dashboard
- Baixar arquivo dashboard.json clicando em Save Dashboard no painel de configuração do dashboard
- Salvar arquivo na raiz do projeto em /src/main/webapp/
- Ao navegar pela URL do dashboard, passar a referencia do arquivo importado (http://dashboard-garden.appspot.com/#source=nome_arquivo.json)

## Configurações Dashboard
- Evento para editar configurações bloqueado. Para habilitar, mudar ("allow_edit": false) para ("allow_edit": true) no arquivo dashboard.json

## Execução
- Localhost:
    - $ clean install appengine:devserver
        - http://localhost:8080/
        - http://localhost:8080/_ah/api/explorer
        - http://localhost:8080/_ah/admin
- Servidor:
    - $ clean install appengine:update
        - http://dashboard-garden.appspot.com/#source=dashboard.json

[1]: http://dashboard-garden.appspot.com/#source=dashboard.json
[2]: https://github.com/Freeboard/freeboard
[3]:  https://cloud.google.com/
[4]: https://cloud.google.com/appengine/docs/java/tools/maven