#include "Server.hpp"

// 1. Diretivas que começam com '#' são comentários e serão ignorados.
// 2. Organizarei em blocos de diretivas, nenhuma diretiva fora de um bloco será aceita, pois fora
// de um bloco não possuí contexto suficiente para ser interpretado.
// 3. Todas as diretivas devem encerrarem com ';' se não serão consideradas erros de sintaxe.
// 4. Os ';' delimitam uma diretiva, sendo assim a diretiva encerrará somente com ';'
// 5. Diretivas necessárias que o arquivo de configuração devem comtemplar: 
// 5.1 "port, host" (para cada servidor [Obrigatório])
// 5.2 server_names ([Não obrigatório]),
// 5.3 O primeiro servidor configurado para determinada host:port será o único
// a ser considerado para aquele servidor, caso tenha no mesmo arquivo de configuração,
// a configuração de um servidor para o mesmo host:port ele será ignorado ([Obrigatório]).
// 5.4 Configurar o limit do body no qual o cliente pode enviar,
// (comprimento máximo do content-lenght no header da requisição [Obrigatório]).
// 5.5 Configurar rotas com um ou múltiplas das regras e configurações à seguir
// 	([Todos obrigatórios]):
// 	5.5.1 Definir uma lista de métodos HTTP aceitos para rota
// 	5.5.2 Definir uma redireção HTTP
//	5.5.3 Definir um diretório ou arquivo que um arquivo deve ser procurado (exemplo se uma url
//	se a url /marcal é roteada para /tmp/www, a url /marcal/arquivos será a url
//	/tmp/www/marcal/arquivos).
//	5.5.4 Permintir a listagem de diretórios ou não.
//	5.5.5 Definir um arquivo padrão para devolver o response caso a requisição tenha sido feita
//	para um recurso que é um diretório.
//	5.5.6 Executar CGI baseado em certas extensões de arquivos (por exemplo .php)
//	5.5.7 Deve funcionar com os métodos POST e GET.
//	5.5.8 Fazer uma rota ser capaz de aceitar arquivos enviados e configurar onde eles devem
//	serem salvos.
//	5.5.9 (Observações): 
//		5.5.9.1 O que é um CGI?
//		5.5.9.2 Como você não chamará o CGI diretamente, usde o caminho completo como PATH_INFO
//		5.5.9.3 Lembre-se que para requisições em pedaços seu servidor deve trazer o contéudo todo
//		e o CGI vai esperar EOF como o final de um body.
//		5.5.9.4 Se content-lenght não é retornado do CGI, o EOF mais determinar o final dos dados
//		retornados.
//		5.5.9.5 Seu programa deve chamar o CGI com o recurso requisitado como primeiro argumento.
//		5.5.9.6	O CGI deve rodar no diretório correto para caminhos de arquivos relativo
//		5.5.9.7	Seu servidor deve roda com um CGI.
//	Observação: Você deve fornecer arquivos de configuração e arquivos padrões básicos para testar
//	e demonstrar que cada funcionalidade funciona durante à avaliação!


void	Server::parserConfig(const std::string &pathname) {
	std::ifstream configFile(pathname);

	if (configFile.fail()) {
		std::cerr << "Error: to open read file" << std::endl;
	}

}