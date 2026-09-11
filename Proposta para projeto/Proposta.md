Estação de Monitoramento de Qualidade do Ar Interno (Ambiente de Trabalho/Estudo)

O Problema: Salas fechadas com muitas pessoas acumulam dióxido de carbono e abafamento, causando sonolência e baixa produtividade, além de monitorar a temperatura e umidade de ambientes sensíveis (como salas de servidores ou farmácias).

O Hardware:1x ESP32.1x Sensor DHT11 ou DHT22 (Temperatura e Umidade) ou um sensor de gás simples como o MQ-135.

Como funciona a IoT: O ESP32 mede a temperatura e umidade da sala em tempo real e envia para a nuvem. Na interface (Dashboard), o grupo monta gráficos de linha bonitos que mostram a variação ao longo do dia. É possível programar uma regra para acender um LED vermelho na mesa (ou enviar um alerta) se a temperatura ultrapassar um limite de conforto térmico.
